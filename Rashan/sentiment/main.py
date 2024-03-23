from textblob import TextBlob
import csv
import re
import operator

def strip_non_ascii(string):
    return ''.join(c for c in string if 0 < ord(c) < 127)

def load_tweets(file_name):
    tweets = []
    with open(file_name, 'r', encoding='latin-1') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        next(reader)
        for row in reader:
            tweet = dict()
            tweet['orig'] = row[0]
            tweet['id'] = int(row[1])
            tweet['pubdate'] = int(row[2])

            if re.match(r'^RT.*', tweet['orig']):
                continue

            tweet['clean'] = tweet['orig']
            tweet['clean'] = strip_non_ascii(tweet['clean'])
            tweet['clean'] = tweet['clean'].lower()
            tweet['clean'] = re.sub(r'http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+', '', tweet['clean'])
            tweet['clean'] = re.sub(r'\bthats\b', 'that is', tweet['clean'])
            tweet['clean'] = re.sub(r'\bive\b', 'i have', tweet['clean'])
            tweet['clean'] = re.sub(r'\bim\b', 'i am', tweet['clean'])
            tweet['clean'] = re.sub(r'\bya\b', 'yeah', tweet['clean'])
            tweet['clean'] = re.sub(r'\bcant\b', 'can not', tweet['clean'])
            tweet['clean'] = re.sub(r'\bwont\b', 'will not', tweet['clean'])
            tweet['clean'] = re.sub(r'\bid\b', 'i would', tweet['clean'])
            tweet['clean'] = re.sub(r'wtf', 'what the fuck', tweet['clean'])
            tweet['clean'] = re.sub(r'\bwth\b', 'what the hell', tweet['clean'])
            tweet['clean'] = re.sub(r'\br\b', 'are', tweet['clean'])
            tweet['clean'] = re.sub(r'\bu\b', 'you', tweet['clean'])
            tweet['clean'] = re.sub(r'\bk\b', 'OK', tweet['clean'])
            tweet['clean'] = re.sub(r'\bsux\b', 'sucks', tweet['clean'])
            tweet['clean'] = re.sub(r'\bno+\b', 'no', tweet['clean'])
            tweet['clean'] = re.sub(r'\bcoo+\b', 'cool', tweet['clean'])
            tweet['TextBlob'] = TextBlob(tweet['clean'])
            tweets.append(tweet)
    return tweets

def analyze_sentiment(tweets):
    for tweet in tweets:
        tweet['polarity'] = float(tweet['TextBlob'].sentiment.polarity)
        tweet['subjectivity'] = float(tweet['TextBlob'].sentiment.subjectivity)

        if tweet['polarity'] >= 0.1:
            tweet['sentiment'] = 'positive'
        elif tweet['polarity'] <= -0.1:
            tweet['sentiment'] = 'negative'
        else:
            tweet['sentiment'] = 'neutral'

    tweets_sorted = sorted(tweets, key=lambda k: k['polarity'])

    print("\n\nTOP NEGATIVE TWEETS")
    negative_tweets = [d for d in tweets_sorted if d['sentiment'] == 'negative']
    for tweet in negative_tweets[0:100]:
        print("id=%d, polarity=%.2f, clean=%s" % (tweet['id'], tweet['polarity'], tweet['clean']))

    print("\n\nTOP POSITIVE TWEETS")
    positive_tweets = [d for d in tweets_sorted if d['sentiment'] == 'positive']
    for tweet in positive_tweets[-100:]:
        print("id=%d, polarity=%.2f, clean=%s" % (tweet['id'], tweet['polarity'], tweet['clean']))

    print("\n\nTOP NEUTRAL TWEETS")
    neutral_tweets = [d for d in tweets_sorted if d['sentiment'] == 'neutral']
    for tweet in neutral_tweets[0:500]:
        print("id=%d, polarity=%.2f, clean=%s" % (tweet['id'], tweet['polarity'], tweet['clean']))

def print_nouns_with_double_letters(tweets):
    double_letter_nouns = []
    for tweet in tweets:
        for word, pos in tweet['TextBlob'].tags:
            if pos == 'NN' and any(char * 2 in word for char in word):
                double_letter_nouns.append(word)
    print("\nNouns with Double Letters:")
    print(double_letter_nouns)

def extract_small_nouns(tweets):
    small_nouns = []
    for tweet in tweets:
        for word, pos in tweet['TextBlob'].tags:
            if pos == 'NN':
                small_nouns.append(word)
    print("\nSmall Case Nouns:")
    print(small_nouns)

def main():
    print("Welcome to Tweet Analysis!")
    file_name = 'newtwitter.csv'
    tweets = load_tweets(file_name)
    while True:
        print("\nSelect an option:")
        print("1. Start sentiment analysis")
        print("2. Print nouns with double letters")
        print("3. Extract small case nouns")
        print("4. Exit")
        choice = input("Enter your choice: ")
        if choice == '1':
            analyze_sentiment(tweets)
        elif choice == '2':
            print_nouns_with_double_letters(tweets)
        elif choice == '3':
            extract_small_nouns(tweets)
        elif choice == '4':
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please enter a number between 1 and 4.")

if __name__ == "__main__":
    main()


