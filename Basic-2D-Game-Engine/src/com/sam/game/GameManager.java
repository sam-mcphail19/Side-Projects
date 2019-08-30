package com.sam.game;

import java.awt.event.KeyEvent;

import com.sam.engine.AbstractGame;
import com.sam.engine.GameContainer;
import com.sam.engine.Renderer;
import com.sam.engine.gfx.Image;

public class GameManager extends AbstractGame{
	
	private Image image;
	
	public GameManager() {
		
		image = new Image("/test.png");
		
	}

	@Override
	public void update(GameContainer gc, float dt) {

		if(gc.getInput().isKeyDown(KeyEvent.VK_A)) {
			
		}
		
	}

	@Override
	public void render(GameContainer gc, Renderer r) {

		r.drawImage(image, gc.getInput().getMouseX() - 32, gc.getInput().getMouseY() - 32);
		
	}
	
	public static void main(String[] args) {
		
		GameContainer gc = new GameContainer(new GameManager());
		gc.start();
		
	}

}
