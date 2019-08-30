package pieces;

import java.awt.image.BufferedImage;

import main.Square;
import main.Team;

public class Rook extends Piece{

	public Rook(Square square, Team team) {

		super(square, team);

		image = (BufferedImage) getImageFromFile("images/" + team.colorToString() + "Rook.png");
		
	}

	public int validMove(int newX, int newY) {

		int xDiff = this.squareDiff(newX, this.getLastSquare().getX());
		int yDiff = this.squareDiff(newY, this.getLastSquare().getY());

		//cant move sideways and up and down at the same time
		if(xDiff != 0 && yDiff != 0){
			return -1;
		}

		if(xDiff == 0){//vertical movement
			if(!vertiPathClear(newY)){
				return -1;
			}
		} else{//horizontal movement
			if(!horiPathClear(newX)){
				return -1;
			}
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
