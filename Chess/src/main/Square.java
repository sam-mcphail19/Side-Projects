package main;

import pieces.Piece;

import java.util.ArrayList;

public class Square {

    public String name;
    private int x, y;

    private static final int FIRSTX = 273, FIRSTY = 713, DIFFBETWEENSQUARES = 85;


    public Square(String name, int x, int y){

        this.name = name;
        this.y = y;
        this.x = x;

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

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public static ArrayList<ArrayList<Square>> makeList(){

        ArrayList<ArrayList<Square>> list = new ArrayList<ArrayList<Square>>();

        for(int i=0; i<8; i++){
            list.add(new ArrayList<>());
            for(int j=0; j<8; j++){
                list.get(i).add(new Square(intToLetter(i)+(j+1), FIRSTX+(DIFFBETWEENSQUARES*i), FIRSTY-(DIFFBETWEENSQUARES*j)));
            }
        }

        return list;

    }

    public static Square getSquare(int x, int y){

        ArrayList<Square> col = getSquareCol(x);

        if(col == null || y > col.get(0).getY() + Square.getDiffBetweenSquares()){
            return null;
        }

        for(int i=0; i<col.size(); i++){
            if(y >= col.get(i).getY()){
                return col.get(i);
            }
        }

        return null;

    }

    public static ArrayList<Square> getSquareCol(int x){

        if(x < Game.boardList.get(0).get(0).getX()){
            return null;
        }

        for(int i=0; i<Game.boardList.size(); i++){
            if(x < Game.boardList.get(i).get(0).getX() + Square.getDiffBetweenSquares()){
                return Game.boardList.get(i);
            }
        }

        return null;

    }

    private static String intToLetter(int num){

        switch(num){
            case 0: return "A";
            case 1: return "B";
            case 2: return "C";
            case 3: return "D";
            case 4: return "E";
            case 5: return "F";
            case 6: return "G";
            case 7: return "H";
        }

        return null;

    }

    public Piece checkSquare() {

        for(int i=0; i<Game.handler.object.size(); i++) {
            GameObject tempObj = Game.handler.object.get(i);
            if(tempObj instanceof Piece) {
                if(tempObj.getX() == this.x && tempObj.getY() == this.y) {
                    return (Piece) tempObj;
                }
            }
        }

        return null;

    }

    public static int getDiffBetweenSquares() {
        return DIFFBETWEENSQUARES;
    }

}
