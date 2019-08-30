package pieces;

import java.awt.image.BufferedImage;

import main.Square;
import main.Team;

public class Pawn extends Piece{
	
	private boolean hasMoved = false;

	public Pawn(Square square, Team team) {

		super(square, team);

		image = (BufferedImage) getImageFromFile("images/" + team.colorToString() + "Pawn.png");
		
	}

	public int validMove(int newX, int newY) {

		Square square = Square.getSquare(newX, newY);

		if (square == null){
			return -1;
		}

		int xDiff = this.squareDiff(newX, this.getLastSquare().getX());
		int yDiff = this.squareDiff(newY, this.getLastSquare().getY());

		if ((this.team.colorToString() == "Black" && yDiff < 0) || (this.team.colorToString() == "White" && yDiff > 0)){
			return -1;
		}

		if(Math.abs(yDiff) > 2 || Math.abs(yDiff) == 0){
			return -1;
		}

		if (Math.abs(yDiff) == 2){
			if(this.hasMoved){
				return -1;
			}
			if(Math.abs(xDiff) != 0) {
				return -1;
			}
			if(!vertiPathClear(newY)){
				return -1;
			}
			if(!squareEmpty(newX, newY)){
				return -1;
			}
		}

		if(Math.abs(yDiff) == 1){
			if (Math.abs(xDiff) == 0) {
				if(!squareEmpty(newX, newY)){
					return -1;
				}
			} else if(Math.abs(xDiff) == 1){
				if(squareHasEnemyPiece(newX, newY)){
					return 1;
				} else {
					return -1;
				}
			} else {//xDiff of anything other than 0 or 1
				return -1;
			}
		}
		return 0;
	}

	public void setHasMoved(boolean hasMoved){
		this.hasMoved = hasMoved;
	}

}
