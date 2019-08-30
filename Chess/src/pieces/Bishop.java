package pieces;

import main.Square;
import main.Team;

import java.awt.image.BufferedImage;

public class Bishop extends Piece{

	public Bishop(Square square, Team team) {

		super(square, team);

		image = (BufferedImage) getImageFromFile("images/" + team.colorToString() + "Bishop.png");
		
	}

	public int validMove(int newX, int newY) {

		int xDiff = this.squareDiff(newX, this.getLastSquare().getX());
		int yDiff = this.squareDiff(newY, this.getLastSquare().getY());

		//must move diagonal
		if(Math.abs(xDiff) != Math.abs(yDiff)){
			return -1;
		}

		if(!diagPathClear(newX, newY)){
			return -1;
		}

		if(!squareEmpty(newX, newY)) {
			if (squareHasEnemyPiece(newX, newY)) {
				return 1;
			} else {
				return -1;
			}
		}
		return 0;
	}

}
