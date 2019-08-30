package main;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import pieces.Pawn;
import pieces.Piece;

public class Input implements MouseListener{

	private Game game;

	private boolean haveSelection = false;
	private Piece selected;
	private Square square;

	Input(Game game){
		this.game = game;
	}

	public void mouseClicked(MouseEvent arg0) {}

	public void mouseEntered(MouseEvent arg0) {}

	public void mouseExited(MouseEvent arg0) {}

	public void mousePressed(MouseEvent arg0) {

		if(game.pawnMenu.getShow()){
			MenuFeature choice = game.pawnMenu.getChoice(arg0.getX(), arg0.getY());
			game.pawnMenu.choiceAction(choice.getName());
			game.pawnMenu.setPawn(null);
			game.pawnMenu.setShow(false);
			return;
		}

		square = Square.getSquare(arg0.getX(), arg0.getY());

		if(square == null){
			return;
		}

		if (!haveSelection) {
			selected = square.checkSquare();
			if (selected != null && selected.getTeam() == game.getCurrentTeam()) {
				haveSelection = true;
				selected.setCurrentlySelected(true);
				for(Move move : selected.genValidMoves()){
					if(move.getValid()) {
						Game.greenSquares.add(new GreenSquare(move.getDest().getX(), move.getDest().getY()));
					}
				}
			}
		} else {
			if (square == selected.getLastSquare()) {//player can put the piece back down
				selected.setX(square.getX());
				selected.setY(square.getY());
				selected.setCurrentlySelected(false);
				haveSelection = false;
			} else {//selected.validMove(square.getX(), square.getY());
				Move move = new Move(selected, square);
				if (!move.getValid()){
					System.out.println("Invalid move");
					return;
				} else {
					if(selected.validMove(square.getX(), square.getY()) > 0){
						selected.takePiece(square.checkSquare());
					}
					selected.setX(square.getX());
					selected.setY(square.getY());
					selected.setCurrentlySelected(false);
					selected.setLastSquare(square);
					haveSelection = false;
					if(selected instanceof Pawn){
						Pawn pawn = (Pawn)selected;
						pawn.setHasMoved(true);
						if((pawn.getTeam() == game.black && pawn.getY() == Game.boardList.get(0).get(0).getY())
						|| (pawn.getTeam() == game.white && pawn.getY() == Game.boardList.get(0).get(7).getY())){
							game.pawnMenu.setShow(true);
							game.pawnMenu.setPawn(pawn);
							game.pawnMenu.setX(game.pawnMenu.getXFromPawn());
							game.pawnMenu.setY(game.pawnMenu.getYFromPawn());
						}
					}
				}

				if(game.isCheck()){
					if(game.getCurrentTeam() == game.white) {
						game.redSquare.setX(game.black.getKing().getLastSquare().getX());
						game.redSquare.setY(game.black.getKing().getLastSquare().getY());
					} else {
						game.redSquare.setX(game.white.getKing().getLastSquare().getX());
						game.redSquare.setY(game.white.getKing().getLastSquare().getY());
					}
					game.redSquare.setInCheck(true);
				} else {
					game.redSquare.setInCheck(false);
				}

				if (game.isCheckmate()){
					game.blackTimer.setStopped(true);
					game.whiteTimer.setStopped(true);
					game.currentTurn.setValue("Checkmate, " + game.getCurrentTeam() + " wins!");
					game.setCurrentTeam(null);
				} else {
					if (game.getCurrentTeam() == game.white) {
						game.setCurrentTeam(game.black);
					} else {
						game.setCurrentTeam(game.white);
					}
					game.currentTurn.setValue("Current Turn: " + game.getCurrentTeam().toString());
				}
			}
			GreenSquare.free();
		}
	}

	public void mouseReleased(MouseEvent arg0) {}

}
