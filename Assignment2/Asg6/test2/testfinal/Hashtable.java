/**
 * Cop 353
 * Assignment 6 
 * Hashtable DataStructures
 */
public class Hashtable {
    private static final int HASHTABLE_SIZE = 16;
    private Object mKeys[] = new Object[HASHTABLE_SIZE];
    private Object mObjects[] = new Object[HASHTABLE_SIZE];

    public void add(Object key, Object object) throws Exception {
        int i = 0;
        int index;
        do {
            index = getLinearProbIndex(key, i);
            if (mKeys[index] == null) {
                mKeys[index] = key;
                mObjects[index] = object;
                return;
            } else {
                i++;
            }
        } while (i < HASHTABLE_SIZE);
        throw new Exception("hash table overflow");
    }

    public void delete(Object key) {
        int i = 0;
        int index;
        do {
            index = getLinearProbIndex(key, i);
            if (mKeys[index] != null && mKeys[index].equals(key)) {
                mKeys[index] = null;
                mObjects[index] = null;
                return;
            } else {
                i++;
            }
        } while (i < HASHTABLE_SIZE);
    }

    public Object get(Object key) {
        int i = 0;
        int index;
        do {
            index = getLinearProbIndex(key, i);
            if (mKeys[index] != null && mKeys[index].equals(key)) {
                return mObjects[index];
            }
            i++;
        } while (i < HASHTABLE_SIZE);
        return null;
    }

    /*
     * Linear Probing index computation
     */
    int getLinearProbIndex(Object key, int i) {
        int k = Math.abs(key.hashCode());
        int h1 = k % HASHTABLE_SIZE;
        return (h1 + i) % HASHTABLE_SIZE;
    }

    /*
     *  Quadratic Probing index computation
     */
    int getQuadraticProbIndex(Object key, int i) {
        int k = Math.abs(key.hashCode());
        int h1 = k % HASHTABLE_SIZE;
        return (h1 + i * i) % HASHTABLE_SIZE;
    }

    /*
     *  Double Hashing index computation
     */
    int getDoubleHash(Object key, int i) {
        int k = Math.abs(key.hashCode());
        int h1 = k % HASHTABLE_SIZE;
        int h2 = 1 + (k % (HASHTABLE_SIZE - 1));
        return (h1 + i * h2) % HASHTABLE_SIZE;
    }

    public static void main(String[] args) {
        Hashtable ht = new Hashtable();
        Integer integer = new Integer(123);
        String string = new String("Hashtable");
        try {
            ht.add("Test", integer);
            ht.add(2, string);
            ht.add("Hashtable", new String("XYZ"));
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println(ht.get("Test"));
        System.out.println(ht.get(2));
        System.out.println(ht.get("Hashtable"));
    }
}

