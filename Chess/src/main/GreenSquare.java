package main;

import java.awt.*;
import java.awt.image.BufferedImage;

public class GreenSquare extends GameObject {

    private static int offsetX = 14, offsetY=9;

    public GreenSquare(int x, int y){
        super(x, y);
        image = (BufferedImage) getImageFromFile("images/greenSquare.png");
    }

    public void tick() {}

    public void render(Graphics g) {
        g.drawImage(image, x-offsetX, y-offsetY, null);
    }

    public static void free(){
        for(int i=0; i<Game.greenSquares.size(); i++){
            GameObject obj = Game.greenSquares.get(i);
            Game.greenSquares.remove(obj);
            obj = null;
            i--;
        }
    }

}
