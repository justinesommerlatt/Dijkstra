package application;
	
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;


public class Main extends Application {
	
	public static Stage primaryStage;
	
	@Override
	public void start(Stage primaryStage) {
		try {	
			this.primaryStage = primaryStage;
			Parent root = FXMLLoader.load(getClass().getResource("vueFenetre.fxml"));
			Scene scene = new Scene(root, 1200, 950);
			primaryStage.setScene(scene);
			primaryStage.show();		
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
