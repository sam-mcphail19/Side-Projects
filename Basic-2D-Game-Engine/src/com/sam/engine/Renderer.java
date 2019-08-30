package com.sam.engine;

import java.awt.image.DataBufferInt;

import com.sam.engine.gfx.Image;

public class Renderer {

	private int pW, pH;
	private int[] p;
	
	public Renderer(GameContainer gc) {
		
		pW = gc.getWidth();
		pH = gc.getHeight();
		
		//gives p direct access to pixel access in the window
		p = ((DataBufferInt)gc.getWindow().getImage().getRaster().getDataBuffer()).getData();
		
	}
	
	public void clear() {
		
		for(int i=0; i < p.length; i++) {
			
			//normally could just set to black 0xff000000
			//p[i] += i;//makes cool rainbow light show
			p[i] = 0;
			
		}
		
	}
	
	public void setPixel(int x, int y, int value) {
		
		if((x < 0 || x >= pW || y < 0 || y >= pH) || value == 0xffff00ff) {//random shade of pink to use as the alpha
			return;
		}
		
		p[x + y * pW] = value;
		
	}
	
	public void drawImage(Image image, double offX, double offY) {
		
		int newX = 0;
		int newY = 0;
		int newWidth = image.getW();
		int newHeight = image.getH();
		
		//"Don't Render" code
		if(offX < -newWidth) {
			return;
		}
		if(offY < -newHeight) {
			return;
		}
		if(offX >= pW) {
			return;
		}
		if(offY >= pH) {
			return;
		}
		
		//"Clipping" code
		if(offX < 0 ) {
			newX -= offX; 
		}
		if(offY < 0 ) {
			newY -= offY; 
		}
		if(newWidth + offX >= pW) {
			newWidth -= newWidth + offX - pW;//-= how far off screen it goes
		}
		if(newHeight + offY >= pH) {
			newHeight -= newHeight + offY - pH;//-= how far off screen it goes
		}
		for(int y = newY; y < newHeight; y++) {
			
			for(int x = newX; x < newWidth; x++) {
				
				setPixel((int)(x + offX), (int)(y + offY), image.getP()[x + y * image.getW()]);
				
			}
			
		}
		
	}
	
}
