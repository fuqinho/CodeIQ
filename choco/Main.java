import java.math.BigInteger;
import java.util.ArrayList;

class Factor {
	public BigInteger prime;
	public int exponent;
	Factor(BigInteger p, int e) { prime = p; exponent = e; }
}

public class Main {	
	public static void main(String[] args) {
		BigInteger N = new BigInteger("280671392065546467397265294532969672241810318954163887187279320454220348884327");
		ArrayList<Factor> factors = factorize(N);
		BigInteger[] answer = findBest(0, BigInteger.ONE, BigInteger.ONE, factors, N);
		if (answer.length != 0)
			System.out.println(answer[1].toString() + "x" + answer[2].toString() + "x" + answer[3].toString());
	}

	private static ArrayList<Factor> factorize(BigInteger N) {
		ArrayList<Factor> res = new ArrayList<Factor>();
		for (BigInteger i = BigInteger.valueOf(2); i.multiply(i).compareTo(N) <= 0; i = i.add(BigInteger.ONE)) {
			int count = 0;
			while (N.remainder(i) == BigInteger.ZERO) {
				count++;
				N = N.divide(i);
			}
			if (count > 0) res.add(new Factor(i, count));
		}
		if (N != BigInteger.ONE) res.add(new Factor(N, 1));
		return res;
	}
		
	private static BigInteger[] findBest(int idx, BigInteger x, BigInteger y, ArrayList<Factor> factors, BigInteger N) {
		if (idx == factors.size()) {
			BigInteger z = N.divide(x).divide(y);
			if (x.compareTo(y) <= 0 && y.compareTo(z) <= 0) {
				BigInteger area = (x.multiply(y)).add(y.multiply(z)).add(z.multiply(x));
				return new BigInteger[] {area, x, y, z};
			} else {
				return new BigInteger[0];
			}
		} else {
			Factor f = factors.get(idx);
			BigInteger[] best = new BigInteger[0];
			for (int ex = 0; ex <= f.exponent; ex++) {
				for (int ey = 0; ex + ey <= f.exponent; ey++) {
					BigInteger nx = x.multiply(f.prime.pow(ex));
					BigInteger ny = y.multiply(f.prime.pow(ey));
					best = getBetter(best, findBest(idx+1, nx, ny, factors, N));
				}
			}
			return best;
		}
	}
	
	private static BigInteger[] getBetter(BigInteger[] a, BigInteger[] b) {
		if (a.length == 0) return b;
		if (b.length == 0) return a;
		return a[0].compareTo(b[0]) < 0 ? a : b;
	}
}
