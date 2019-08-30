package main;

import pieces.Piece;

public class Move {

    private Piece piece;
    private Square dest;
    private boolean valid;

    public Move(Piece piece, Square dest){
        this.piece = piece;
        this.dest = dest;
        this.valid = piece.validMove(dest.getX(), dest.getY()) >= 0 && !leavesKingInCheck();
    }

    private boolean leavesKingInCheck(){
        boolean result = false;

        int tempX = piece.getLastSquare().getX();
        int tempY = piece.getLastSquare().getY();

        //temporarily move the piece to the new square
        piece.setX(dest.getX());
        piece.setY(dest.getY());
        piece.setLastSquare(Square.getSquare(dest.getX(), dest.getY()));

        //if any piece on the other team is checking this piece's king
        for(GameObject obj : Handler.object){
            if(obj instanceof Piece){
                Piece checkPiece = (Piece) obj;
                if(checkPiece.getTeam() != piece.getTeam() && !checkPiece.isDead() && checkPiece.isChecking()){
                    result = true;
                    break;
                }
            }
        }

        //move the piece back to where it was
        piece.setX(tempX);
        piece.setY(tempY);
        piece.setLastSquare(Square.getSquare(tempX, tempY));
        return result;
    }

    public String toString() {
        return piece.getTeam() + " " + piece.getClass() + " to " + dest.getName();
    }

    public Piece getPiece() {
        return piece;
    }

    public void setPiece(Piece piece) {
        this.piece = piece;
    }

    public Square getDest() {
        return dest;
    }

    public boolean getValid() {
        return valid;
    }

}
