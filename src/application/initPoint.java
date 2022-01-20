package application;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;





public class initPoint {

	private List<Point> listePoints = new ArrayList<Point>(); // liste de points
	private List<Ville> listeVilles = new ArrayList<Ville>(); // liste de villes 
	
	public initPoint(String filename) throws NumberFormatException, IOException {
	
		String line;
		Ville ville;
		List<Point> listePoints = new ArrayList<Point>(); // liste de points
		List<Ville> listeVilles = new ArrayList<Ville>(); // liste de villes 
		List<String> listePred = new ArrayList<String>(); // liste des predecesseurs 
	
		BufferedReader br = null;
		
		br = new BufferedReader(new FileReader(filename));
		
		int nbNoeuds = Integer.parseInt(br.readLine()); // nombre de noeud du graphe
		int radius; 
		Point centre;
		if( nbNoeuds == 10) {
			centre = new Point(null, 350, 450); // placement du centre � la main suivant la taille de notre fenetre finale
			radius = 300;
		}else {
			centre = new Point(null, 470, 450); // placement du centre � la main suivant la taille de notre fenetre finale
			radius = 450;
		}
		double angle = Math.toRadians(360/nbNoeuds); // calcule de l'angle qui nous permettra de definir les coordon�es des points sur notre cercle
	
		for (int i=0; i<nbNoeuds; i++) { // pour chaque noeud determiation des coordonn�es et cr�ation d'un point
			
			double theta = i*angle;
			int dx = (int)(radius * Math.sin(theta));
			int dy = (int)(-radius * Math.cos(theta));
			
			line = br.readLine();
			if ( i == 0) {
				ville = new Ville(line, "0", null);
			}
			else {
				String[] arrayOfString = line.split(" ", 3);
				String name = arrayOfString[0];
				String dist = arrayOfString[1];
				String pred = arrayOfString[2];
				ville = new Ville(name,dist,null);
				listePred.add(pred);
			}
			listeVilles.add(ville);	
			Point p = new Point(ville, centre.getX() + dx, centre.getY() + dy);
			listePoints.add(p); // ajout du point � la liste de points
		}
		br.close();	
		
		// maintenant que toutes les villes sont cr��es on va remplir leur champ pred avec la bonne ville 
		for ( int i = 1; i < listePoints.size(); i++) {
			Point p = listePoints.get(i);
			String s = listePred.get(i-1);
			for ( int j =0; j < listeVilles.size(); j++) {
				String v = listeVilles.get(j).getName();
				if (s.contentEquals(v)) {
					p.getVille().setPred(listeVilles.get(j));
				}
			}
		}
		
		this.listePoints = listePoints;
		this.listeVilles = listeVilles;
	}
	
	public ArrayList<Point> getListePoints(){
		return (ArrayList<Point>) listePoints;
	}
	
	public ArrayList<Ville> getListeVilles(){
		return (ArrayList<Ville>) listeVilles;
	}
	

}