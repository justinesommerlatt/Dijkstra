package application;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Graph {

	List<Point> listePoints = new ArrayList<Point>(); // liste des points du graphe
	List<Ville> listeVilles = new ArrayList<Ville>(); // liste de villes 
	
	public Graph(String filename) throws NumberFormatException, IOException {
		initPoint IP = new initPoint(filename);
		this.listePoints = IP.getListePoints(); 
		this.listeVilles = IP.getListeVilles();
	}
}
