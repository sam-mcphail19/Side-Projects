package pieces;

import java.awt.Graphics;
import java.awt.MouseInfo;
import java.util.ArrayList;

import main.*;

public abstract class Piece extends GameObject{

	boolean isDead = false;
	private Square lastSquare;
	public Team team;
	
	public Piece(Square square, Team team) {
		super(square.getX(), square.getY());
		this.lastSquare = square;
		this.team = team;
	}

	public void tick(){
		
		if(currentlySelected && !isDead) {
			this.x = (int) MouseInfo.getPointerInfo().getLocation().getX() - 390;
			this.y = (int) MouseInfo.getPointerInfo().getLocation().getY() - 130;
		}

		if(!currentlySelected && !isDead){
		    this.x = this.getLastSquare().getX();
		    this.y = this.getLastSquare().getY();
        }
		
	}
	
	public void render(Graphics g){
		
		g.drawImage(image, x, y, null);
		
	}

	//negative if move is invalid, 0 if the move is valid, 1 if the move is valid and
	//involves taking an enemy piece
	public abstract int validMove(int newX, int newY);
	
	//returns amount of squares the piece will move side in one dimension (x or y)
	public int squareDiff(int newPos, int oldPos) {
		return (newPos - oldPos) / Square.getDiffBetweenSquares();
	}

	public boolean squareHasEnemyPiece(int x, int y){
		Square square = Square.getSquare(x,y);
		Piece piece = square.checkSquare();

		if(piece == null){
			return false;
		}

		return (piece.team.getColor() != this.team.getColor());
	}

	public boolean squareEmpty(int x, int y){
		Square square = Square.getSquare(x,y);
		Piece piece = square.checkSquare();

		return (piece == null);

	}


	public void takePiece(Piece piece){

		//move object to end of GameObject list so things are drawn overlapping in a sensible order
		Handler.removeObject(piece);
		Handler.addObject(piece);

		piece.setX(piece.getTeam().getLastRemovedX());
		piece.setY(piece.getTeam().getLastRemovedY());
		piece.setDead(true);

	}

    public boolean horiPathClear(int newX){
        ArrayList<Square> row = this.getRow();

        if(newX < this.getLastSquare().getX()){//moving left
            for(int i=0; i<row.size(); i++){
                Square square = row.get(i);
                if(newX < square.getX() && square.getX() < this.getLastSquare().getX()) {
                    if (square.checkSquare() != null) {
                        return false;
                    }
                }
            }
        } else {//moving right
            for(int i=0; i<row.size(); i++){
                Square square = row.get(i);
                if(this.getLastSquare().getX() < square.getX() && square.getX() < newX) {
                    if (square.checkSquare() != null) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

	public boolean vertiPathClear(int newY){
        ArrayList<Square> col = this.getCol();

        if(newY < this.getLastSquare().getY()){//moving up
            for(int i=0; i<col.size(); i++){
                Square square = col.get(i);
                if(newY < square.getY() && square.getY() < this.getLastSquare().getY()) {
                    if (square.checkSquare() != null) {
                        return false;
                    }
                }
            }
        } else {//moving down
            for(int i=0; i<col.size(); i++){
                Square square = col.get(i);
                if(this.getLastSquare().getY() < square.getY() && square.getY() < newY) {
                    if (square.checkSquare() != null) {
                        return false;
                    }
                }
            }
        }
        return true;
	}

	boolean diagPathClear(int newX, int newY){

		//4 cases - going up left, up right, down left, down right

		//moving right
		if(newX > this.getLastSquare().getX()){

			//moving down
			if(newY > this.getLastSquare().getY()){

				for(ArrayList<Square> col : Game.boardList){
					for(Square square : col){
						int xDiff = this.squareDiff(square.getX(), this.getLastSquare().getX());
						int yDiff = this.squareDiff(square.getY(), this.getLastSquare().getY());
						//moving diagonally
						if(xDiff == yDiff){
							//new value below the one being checked, and the one being checked is below the current value
							if(newY > square.getY() && square.getY() > this.getLastSquare().getY()){
								if(newX > square.getX() && square.getX() > this.getLastSquare().getX()){
									if(square.checkSquare() != null){
										return false;
									}
								}
							}
						}
					}
				}

			} else {//moving up

				for(ArrayList<Square> col : Game.boardList){
					for(Square square : col){
						int xDiff = this.squareDiff(square.getX(), this.getLastSquare().getX());
						int yDiff = this.squareDiff(square.getY(), this.getLastSquare().getY());
						//moving diagonally
						if(xDiff == -yDiff){
							//new value below the one being checked, and the one being checked is below the current value
							if(newY < square.getY() && square.getY() < this.getLastSquare().getY()){
								if(newX > square.getX() && square.getX() > this.getLastSquare().getX()){
									if(square.checkSquare() != null){
										return false;
									}
								}
							}
						}
					}
				}

			}

		} else {//moving left

			//moving down
			if(newY > this.getLastSquare().getY()){

				for(ArrayList<Square> col : Game.boardList){
					for(Square square : col){
						int xDiff = this.squareDiff(square.getX(), this.getLastSquare().getX());
						int yDiff = this.squareDiff(square.getY(), this.getLastSquare().getY());
						//moving diagonally
						if(xDiff == -yDiff){
							//new value below the one being checked, and the one being checked is below the current value
							if(newY > square.getY() && square.getY() > this.getLastSquare().getY()){
								if(newX < square.getX() && square.getX() < this.getLastSquare().getX()){
									if(square.checkSquare() != null){
										return false;
									}
								}
							}
						}
					}
				}

			} else {//moving up

				for(ArrayList<Square> col : Game.boardList){
					for(Square square : col){
						int xDiff = this.squareDiff(square.getX(), this.getLastSquare().getX());
						int yDiff = this.squareDiff(square.getY(), this.getLastSquare().getY());
						//moving diagonally
						if(xDiff == yDiff){
							//new value below the one being checked, and the one being checked is below the current value
							if(newY < square.getY() && square.getY() < this.getLastSquare().getY()){
								if(newX < square.getX() && square.getX() < this.getLastSquare().getX()){
									if(square.checkSquare() != null){
										return false;
									}
								}
							}
						}
					}
				}

			}

		}

		return true;

	}

	private ArrayList<Square> getCol(){
	    for(int i=0; i<Game.boardList.size(); i++){
	        if(this.getLastSquare().getX() == Game.boardList.get(i).get(0).getX()){
	            return Game.boardList.get(i);
            }
        }
	    return null;
    }

    private ArrayList<Square> getRow(){
	    ArrayList<Square> result = new ArrayList<>();
	    for(int i=0; i<Game.boardList.size(); i++){
	        if(this.getLastSquare().getY() == Game.boardList.get(0).get(i).getY()){
	            for(int j=0; j<Game.boardList.size(); j++){
	                result.add(Game.boardList.get(j).get(i));
                }
	            return result;
            }
        }
	    return null;
    }

    public boolean isChecking(){
	    Piece king;
	    if(this.getTeam() == Game.white){
	        king = Game.black.getKing();
        } else {
	        king = Game.white.getKing();
        }
        return this.validMove(king.getLastSquare().getX(), king.getLastSquare().getY()) >= 0;
	}

    public ArrayList<Move> genValidMoves(){
		ArrayList<Move> validMoves = new ArrayList<>();
		for(ArrayList<Square> row : Game.boardList){

			for(Square square : row){
				Move move = new Move(this, square);
				if(move.getValid()){
					validMoves.add(move);
				}

			}

		}
		return validMoves;
	}

	public Team getTeam(){
		return this.team;
	}

	public void setDead(boolean bool){
		isDead = bool;
	}

	public boolean isDead(){
		return this.isDead;
	}

	public Square getLastSquare() {
		return lastSquare;
	}

	public void setLastSquare(Square square){
		this.lastSquare = square;
	}

}
