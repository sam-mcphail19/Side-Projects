package pieces;

import main.Square;
import main.Team;

import java.awt.image.BufferedImage;

public class Queen extends Piece{

	public Queen(Square square, Team team) {

		super(square, team);

		image = (BufferedImage) getImageFromFile("images/" + team.colorToString() + "Queen.png");
		
	}

	public int validMove(int newX, int newY) {

		int xDiff = this.squareDiff(newX, this.getLastSquare().getX());
		int yDiff = this.squareDiff(newY, this.getLastSquare().getY());

		if(Math.abs(xDiff) == 0 || Math.abs(yDiff) == 0){//non diagonal movement
			if(xDiff == 0){//vertical movement
				if(!vertiPathClear(newY)){
					return -1;
				}
			}
			if(yDiff == 0){//horizontal movement
				if(!horiPathClear(newX)){
					return -1;
				}
			}
		} else if(Math.abs(xDiff) == Math.abs(yDiff)){//diagonal movement
			if(!diagPathClear(newX, newY)){
				return -1;
			}
		} else {//not horizontal, vertical, or diagonal
			return -1;
		}

		if(!squareEmpty(newX, newY)){
			if(squareHasEnemyPiece(newX, newY)){
				return 1;
			} else{
				return -1;
			}
		}
		return 0;
	}

}
