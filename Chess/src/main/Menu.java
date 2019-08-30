package main;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class Menu extends GameObject{

    private boolean show = false;
    private ArrayList<MenuFeature> features = new ArrayList<>();

    Menu(int x, int y, String imagePath){
        super(x, y);
        this.image = (BufferedImage) getImageFromFile(imagePath);
    }

    public void tick() {
        for(MenuFeature feature : this.features){
            feature.tick();
        }
    }

    public void render(Graphics g) {
        if(show){
            g.drawImage(image, x, y, null);
            for(MenuFeature feature : this.features){
                g.drawImage(feature.image, feature.getX(), feature.getY(), null);
            }
        }
    }

    void addFeature(MenuFeature newFeature){
        features.add(newFeature);
    }

    public MenuFeature getChoice(int x, int y){
        if(x < this.x || this.x + this.image.getWidth() < x){
            return null;
        }

        if(y < this.y || this.y + this.image.getHeight() < y){
            return null;
        }

        for(MenuFeature feature : features){
            if(this.x + feature.relativeX < x && x < this.x + feature.relativeX + feature.image.getWidth()){
                if(this.y + feature.relativeY < y && y < this.y + feature.relativeY + feature.image.getHeight()){
                    System.out.println(feature.name);
                    return feature;
                }
            }
        }

        return null;
    }

    public boolean getShow() {
        return show;
    }

    public void setShow(boolean show) {
        this.show = show;
    }

}
