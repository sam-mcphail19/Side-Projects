package main;

import java.awt.*;
import java.awt.image.BufferedImage;

public class RedSquare extends GameObject{

    private boolean inCheck = false;
    private static int offsetX = 14, offsetY=9;

    public RedSquare(int x, int y){
        super(x, y);
        image = (BufferedImage) getImageFromFile("images/redSquare.png");
    }

    public void tick() {}

    public void render(Graphics g) {
        if(inCheck){
            g.drawImage(image, x-offsetX, y-offsetY, null);
        }
    }

    public void setInCheck(boolean value){
        this.inCheck = value;
    }

}
