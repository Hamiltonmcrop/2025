from textblob import TextBlob
import csv
import re
import operator

class Tweet:
    def __init__(self, orig, tweet_id, pubdate):
        self.orig = orig
        self.id = tweet_id
        self.pubdate = pubdate
        self.clean = self.clean_tweet()
        self.text_blob = TextBlob(self.clean)

    def clean_tweet(self):
        clean_tweet = self.orig.lower()
        clean_tweet = re.sub(r'http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+', '', clean_tweet)
        clean_tweet = re.sub(r'\bthats\b', 'that is', clean_tweet)
        clean_tweet = re.sub(r'\bive\b', 'i have', clean_tweet)
        clean_tweet = re.sub(r'\bim\b', 'i am', clean_tweet)
        clean_tweet = re.sub(r'\bya\b', 'yeah', clean_tweet)
        clean_tweet = re.sub(r'\bcant\b', 'can not', clean_tweet)
        clean_tweet = re.sub(r'\bwont\b', 'will not', clean_tweet)
        clean_tweet = re.sub(r'\bid\b', 'i would', clean_tweet)
        clean_tweet = re.sub(r'wtf', 'what the fuck', clean_tweet)
        clean_tweet = re.sub(r'\bwth\b', 'what the hell', clean_tweet)
        clean_tweet = re.sub(r'\br\b', 'are', clean_tweet)
        clean_tweet = re.sub(r'\bu\b', 'you', clean_tweet)
        clean_tweet = re.sub(r'\bk\b', 'OK', clean_tweet)
        clean_tweet = re.sub(r'\bsux\b', 'sucks', clean_tweet)
        clean_tweet = re.sub(r'\bno+\b', 'no', clean_tweet)
        clean_tweet = re.sub(r'\bcoo+\b', 'cool', clean_tweet)
        return clean_tweet

class BaseClass:
    def __init__(self, file_name):
        self.file_name = file_name

    def load_tweets(self):
        tweets = []
        with open(self.file_name, 'r', encoding='latin-1') as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            next(reader)
            for row in reader:
                tweet = Tweet(row[0], int(row[1]), int(row[2]))

                if not re.match(r'^RT.*', tweet.orig):
                    tweets.append(tweet)
        return tweets

class DerivedClass1(BaseClass):
    def analyze_sentiment(self, tweets):
        for tweet in tweets:
            tweet.text_blob = TextBlob(tweet.clean)
            tweet.polarity = float(tweet.text_blob.sentiment.polarity)
            tweet.subjectivity = float(tweet.text_blob.sentiment.subjectivity)

            if tweet.polarity >= 0.1:
                tweet.sentiment = 'positive'
            elif tweet.polarity <= -0.1:
                tweet.sentiment = 'negative'
            else:
                tweet.sentiment = 'neutral'

        tweets_sorted = sorted(tweets, key=lambda k: k.polarity)

        with open("sentiment_analysis_output.txt", "w") as f:
            f.write("\n\nTOP NEGATIVE TWEETS\n")
            negative_tweets = [d for d in tweets_sorted if d.sentiment == 'negative']
            for tweet in negative_tweets[0:100]:
                f.write(f"id={tweet.id}, polarity={tweet.polarity:.2f}, clean={tweet.clean}\n")

            f.write("\n\nTOP POSITIVE TWEETS\n")
            positive_tweets = [d for d in tweets_sorted if d.sentiment == 'positive']
            for tweet in positive_tweets[-100:]:
                f.write(f"id={tweet.id}, polarity={tweet.polarity:.2f}, clean={tweet.clean}\n")

            f.write("\n\nTOP NEUTRAL TWEETS\n")
            neutral_tweets = [d for d in tweets_sorted if d.sentiment == 'neutral']
            for tweet in neutral_tweets[0:500]:
                f.write(f"id={tweet.id}, polarity={tweet.polarity:.2f}, clean={tweet.clean}\n")

class DerivedClass2(BaseClass):
    def print_nouns_with_double_letters(self, tweets):
        double_letter_nouns = []
        for tweet in tweets:
            for word, pos in tweet.text_blob.tags:
                if pos == 'NN' and any(char * 2 in word for char in word):
                    double_letter_nouns.append(word)

        with open("double_letter_nouns_output.txt", "w") as f:
            f.write("\nNouns with Double Letters:\n")
            for noun in double_letter_nouns:
                f.write(noun + "\n")

class DerivedClass3(BaseClass):
    def extract_small_nouns(self, tweets):
        small_nouns = []
        for tweet in tweets:
            for word, pos in tweet.text_blob.tags:
                if pos == 'NN':
                    small_nouns.append(word)

        with open("small_nouns_output.txt", "w") as f:
            f.write("\nSmall Case Nouns:\n")
            for noun in small_nouns:
                f.write(noun + "\n")

def main():
    print("Welcome to Tweet Analysis!")
    file_name = 'newtwitter.csv'
    base = BaseClass(file_name)
    tweets = base.load_tweets()
    
    while True:
        print("\nSelect an option:")
        print("1. Start sentiment analysis")
        print("2. Print nouns with double letters")
        print("3. Extract small case nouns")
        print("4. Exit")
        
        choice = input("Enter your choice: ")
        
        try:
            choice = int(choice)
            if choice == 1:
                derived1 = DerivedClass1(file_name)
                derived1.analyze_sentiment(tweets)
            elif choice == 2:
                derived2 = DerivedClass2(file_name)
                derived2.print_nouns_with_double_letters(tweets)
            elif choice == 3:
                derived3 = DerivedClass3(file_name)
                derived3.extract_small_nouns(tweets)
            elif choice == 4:
                print("Exiting...")
                break
            else:
                print("Invalid choice. Please enter a number between 1 and 4.")
        except ValueError:
            print("Invalid input. Please enter a number.")

if __name__ == "__main__":
    main()

