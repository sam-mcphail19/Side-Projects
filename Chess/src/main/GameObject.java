package main;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public abstract class GameObject {

	protected int x,y;
	protected String imgPath;
	protected BufferedImage image;
	protected boolean currentlySelected = false;

	public GameObject(int x, int y){
		
		this.x = x;
		this.y = y;
		
	}

    public abstract void tick();
	
	public abstract void render(Graphics g);
	
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
	
	public boolean getCurrentlySelected() {
		return currentlySelected;
	}
	
	public void setCurrentlySelected(Boolean currentlySelected) {
		this.currentlySelected = currentlySelected;
	}
	
	protected Image getImageFromFile(String path){
		
		Image image = null;
		File file = new File(path);
		
		try{
			image = ImageIO.read(file);
		} catch(IOException e){
			e.printStackTrace();
		}
		
		return image;
		
	}
	
}
