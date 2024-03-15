//Disa Röed Sahlström, disa7213

public class LinearProbingHashTable<T> extends ProbingHashTable<T> {

	/*
	 * Denna metod ska skrivas klart. Den ska använda linjär sondering och hela tiden öka med ett.
	 */
	@Override
	protected int findPos(T x) {
		int currentPos = myhash(x);
		while(continueProbing(currentPos, x)) {
			currentPos ++;
			if (currentPos >= capacity())
				currentPos -= capacity();
		}
		return currentPos;
	}

}
