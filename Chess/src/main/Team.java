package main;

import pieces.*;

import java.awt.*;

public class Team {

    private enum Colors{

        Black(Color.black),White(Color.white);

        private final Color color;

        Colors(Color color) {
            this.color = color;
        }
    }

    private Colors color;

    private int lastRemovedX = 0, xDiff = 25, yDiff = 50;
    private int lastRemovedY;

    public Team(String color){
        if(color == "White"){
            this.color = Colors.White;
            lastRemovedY = 650;
        } else if(color == "Black"){
            this.color = Colors.Black;
            lastRemovedY = 100;
        }
    }

    public Colors getColor() {
        return color;
    }

    public String colorToString(){
        return color.toString();
    }

    public void setTeam(Colors color) {
        this.color = color;
    }

    public int getLastRemovedX() {
        int newVal = lastRemovedX;
        lastRemovedX += xDiff;
        return newVal;
    }

    public int getLastRemovedY() {
        int newVal = lastRemovedY;
        if(lastRemovedX > 120){
            lastRemovedY += yDiff;
            lastRemovedX = 0;
        }
        return newVal;
    }

    public String toString(){

        return this.colorToString();

    }

    public Piece getKing(){
        for(GameObject obj : Handler.object){
            if (obj instanceof King){
                King king = (King) obj;
                if(king.getTeam().getColor() == this.getColor()){
                    return king;
                }
            }
        }
        return null;
    }
}
