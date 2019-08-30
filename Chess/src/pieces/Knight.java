package pieces;

import java.awt.image.BufferedImage;

import main.Square;
import main.Team;

public class Knight extends Piece{

	public Knight(Square square, Team team) {

		super(square, team);

		image = (BufferedImage) getImageFromFile("images/" + team.colorToString() + "Knight.png");
		
	}

	public int validMove(int newX, int newY) {

		int xDiff = this.squareDiff(newX, this.getLastSquare().getX());
		int yDiff = this.squareDiff(newY, this.getLastSquare().getY());

		//knights move in an "L" shape (2x and 1y or 2y and 1x)

		if(Math.abs(xDiff) == 0 || Math.abs(yDiff) == 0){
			return -1;
		}

		if(Math.abs(xDiff) + Math.abs(yDiff) != 3){
			return -1;
		}

		if(!squareEmpty(newX, newY)){
			if(squareHasEnemyPiece(newX, newY)){
				return 1;
			} else {
				return -1;
			}
		}
		return 0;
	}
	
}
