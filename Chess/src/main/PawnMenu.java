package main;

import pieces.*;

public class PawnMenu extends Menu{

    private int offset = 40;
    private Pawn pawn;
    private final int width, height, featDim=68;

    public PawnMenu(int x, int y, String imagePath){
        super(x, y, imagePath);
        this.width = image.getWidth();
        this.height = image.getHeight();
        this.addFeature(new MenuFeature(width/4 - featDim/2, height/4-featDim/2, "images/blackQueen.png", "Queen", this));
        this.addFeature(new MenuFeature(3*width/4-featDim/2, height/4-featDim/2, "images/blackRook.png", "Rook", this));
        this.addFeature(new MenuFeature(width/4 - featDim/2, 3*height/4 - featDim/2, "images/blackBishop.png", "Bishop", this));
        this.addFeature(new MenuFeature(3*width/4-featDim/2, 3*height/4 - featDim/2, "images/blackKnight.png", "Knight", this));
    }

    public int getXFromPawn(){
        System.out.println(pawn.getX() + " " + Game.WIDTH/2);
        if(pawn.getX() > Game.WIDTH/2){//on the right side
            return pawn.getX() - offset - this.image.getWidth();
        } else {
            return pawn.getX() + offset;
        }
    }

    public int getYFromPawn(){
        if(pawn.getY() > Game.HEIGHT/2){//on the bottom half
            return pawn.getY() - offset - this.image.getHeight();
        } else {
            return pawn.getY() + offset;
        }
    }

    public void choiceAction(String choice){
        Handler.removeObject(pawn);
        switch (choice){
            case "Queen":
                Handler.addObject(new Queen(pawn.getLastSquare(), pawn.getTeam()));
                break;
            case "Bishop":
                Handler.addObject(new Bishop(pawn.getLastSquare(), pawn.getTeam()));
                break;
            case "Rook":
                Handler.addObject(new Rook(pawn.getLastSquare(), pawn.getTeam()));
                break;
            case "Knight":
                Handler.addObject(new Knight(pawn.getLastSquare(), pawn.getTeam()));
                break;
        }
    }

    public void setPawn(Pawn pawn) {
        this.pawn = pawn;
    }
}
