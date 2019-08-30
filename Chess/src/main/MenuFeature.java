package main;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class MenuFeature{

    Menu parent;
    int x, y, relativeX, relativeY;
    BufferedImage image;
    String name;

    public MenuFeature(int relativeX, int relativeY, String imagePath, String name, Menu parent){
        this.relativeX = relativeX;
        this.relativeY = relativeY;
        this.image = getImageFromFile(imagePath);
        this.name = name;
        this.parent = parent;
    }

    public void tick(){
        this.x = this.parent.getX() + this.relativeX;
        this.y = this.parent.getY() + this.relativeY;
    }

    public void render(Graphics g){
        g.drawImage(this.image, this.x, this.y, null);
    }

    private BufferedImage getImageFromFile(String path){

        Image image = null;
        File file = new File(path);

        try{
            image = ImageIO.read(file);
        } catch(IOException e){
            e.printStackTrace();
        }

        return (BufferedImage) image;

    }

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

    public String getName(){
        return name;
    }
}
