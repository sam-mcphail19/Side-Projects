package main;

import java.awt.Graphics;
import java.util.LinkedList;

public class Handler {

	public static LinkedList<GameObject> object = new LinkedList<GameObject>();//ArrayList of all objects in the game
	
	public void tick(){
		
		//loop through all GameObjects and call each one's tick 
		for(int i=0; i<object.size(); i++){
			
			GameObject tempObject = object.get(i);
			
			tempObject.tick();//calling tick from GameObject
			
		}
		
	}
	
	public void render(Graphics g){
		
		////loop through all GameObjects and call each one's render 
		for(int i=0; i<object.size(); i++){
			
			GameObject tempObject = object.get(i);
			
			tempObject.render(g);//calling render from GameObject
			
		}
		
	}
	
	public static void addObject(GameObject newObject){
		
		object.add(newObject);
		
	}
	
	public static void removeObject(GameObject objToRemove){
		
		object.remove(objToRemove);
		
	}
	
}
