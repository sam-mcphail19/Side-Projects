package pieces;

import main.Square;
import main.Team;

import java.awt.image.BufferedImage;

public class King extends Piece{

	public King(Square square, Team team) {

		super(square, team);

		image = (BufferedImage) getImageFromFile("images/" + team.colorToString() + "King.png");
		
	}

	public int validMove(int newX, int newY) {

		int xDiff = this.squareDiff(newX, this.getLastSquare().getX());
		int yDiff = this.squareDiff(newY, this.getLastSquare().getY());

		if(Math.abs(xDiff) > 1 || Math.abs(yDiff) > 1){
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
