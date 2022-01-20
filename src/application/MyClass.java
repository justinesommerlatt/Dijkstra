package application;

public class MyClass {

	public native void Dijkstra(String fileNameIn, String fileNameOut, String Departure, int heapType);
	
	static {
		System.load("/home/etymoi/tp3_dijkstra_vitrac_sommerlatt_troyon/lib/libDij.so");
	}
}
