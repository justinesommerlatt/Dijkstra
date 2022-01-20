package application;

public class Point {
	
	private int x, y;
	private Ville ville;
	
	
	public Point(Ville ville, int x, int y) {
		this.ville = ville;
		this.x = x;
		this.y = y;
	}

	@Override
	public String toString() {
		return "Point [x=" + x + ", y=" + y + ", ville=" + ville + "]";
	}

	public int getX() {
		return x;
	}
	
	public void setX(int x) {
		this.x = x;
	}
	
	public int getY() {
		return y;
	}
	
	public void setY(int y) {
		this.y = y;
	}

	public Ville getVille() {
		return ville;
	}

	public void setVille(Ville ville) {
		this.ville = ville;
	}
	
}
