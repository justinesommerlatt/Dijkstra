package application;

import java.io.File;
import java.io.IOException;

import javax.swing.JFileChooser;


import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class ControllerFenetre {

	@FXML private AnchorPane anchorPane = new AnchorPane();
	@FXML private TextField nomFichier = new TextField();
	@FXML private TextField nomVille = new TextField();
	@FXML private TextField typeHeap = new TextField();
	String pathFichier;
	String ville;
	int type;
	Stage primaryStage = Main.primaryStage;
	
	public ControllerFenetre() {
		
	}
	
	public void initialize() {
		pathFichier = null;
		ville = null;
		type = -1;
	}
	
	public void Fichier(ActionEvent event) {
		JFileChooser fileChooser = new JFileChooser();
		int returnVal = fileChooser.showOpenDialog(null);
			if ( returnVal == JFileChooser.APPROVE_OPTION) {
				File fichier = fileChooser.getSelectedFile();
				pathFichier = fichier.getAbsolutePath();
			}
		
	}
	
	public void Ville(ActionEvent event) {
		ville = nomVille.getText();
	}
	
	public void Type(ActionEvent event) {
		type = Integer.parseInt(((Button)event.getSource()).getId());
	}
	
	public void Dessiner(ActionEvent event) throws NumberFormatException, IOException {
		anchorPane.getChildren().removeAll(anchorPane.getChildren());
		System.out.println(pathFichier);
		System.out.println(ville);
		System.out.println(type);
		if (pathFichier != null && ville != null && (type >=0 && type <=2)) {
			
			new MyClass().Dijkstra(pathFichier, "canevas/resultat", ville, type);
			String filename = "canevas/resultat";
			Graph G = new Graph(filename);
			
			for ( int i = 1; i < G.listePoints.size(); i++) {
				Point p = G.listePoints.get(i);
				for( int j = 0; j < G.listePoints.size(); j++) {
					Point p2 = G.listePoints.get(j);
					if ( p.getVille().getPred().getName().equals(p2.getVille().getName())) {
						int x2 = p2.getX();
						int y2 = p2.getY();
						Line l = new Line(p.getX(), p.getY(), x2, y2);
						l.setStroke(Color.CRIMSON);
						l.setStrokeWidth(4);
						anchorPane.getChildren().addAll(l);
					}
				
					Rectangle ra = new Rectangle(130,50,Color.ORANGE);
					if (p2.getX() > 250) {
						ra.setX(p2.getX());
						ra.setY(p2.getY());
					}
					else {
						ra.setX(p2.getX());
						ra.setY(p2.getY());
					}
					
					
					Text text = new Text(p2.getVille().getName() + " | " + p2.getVille().getDist()+ " km");
					StackPane stack = new StackPane();
					stack.getChildren().addAll(ra,text);
					stack.setLayoutX(p2.getX());
					stack.setLayoutY(p2.getY());
					anchorPane.getChildren().addAll(stack);
				}
			}
		}
		else {
			System.out.println("ERREUR DONNEE");
		}
	}
}
