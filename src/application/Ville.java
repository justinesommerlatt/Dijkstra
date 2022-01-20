package application;

public class Ville {
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Ville other = (Ville) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}

	private String name;
	private String dist;
	private Ville pred;
	
	public Ville(String name, String dist, Ville pred) {
		this.name = name;
		this.dist = dist;
		this.pred = pred;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDist() {
		return dist;
	}

	public void setDist(String dist) {
		this.dist = dist;
	}

	public Ville getPred() {
		return pred;
	}

	public void setPred(Ville pred) {
		this.pred = pred;
	}

	@Override
	public String toString() {
		return "Ville [name=" + name + ", dist=" + dist + ", pred=" + pred + "]";
	}
	
}
