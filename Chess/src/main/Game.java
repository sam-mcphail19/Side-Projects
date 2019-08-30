//TODO:
//

package main;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;

import pieces.*;

public class Game extends Canvas{

	private static final long serialVersionUID = -5651931617882564615L;

	public static Game game;
	
	public static final int WIDTH=1200, HEIGHT= WIDTH / 12 * 9;
	public BufferedImage board = (BufferedImage) getImageFromFile("images/board.png");
	
	static Handler handler;
	
	private Input input;
	
	BufferStrategy bs = this.getBufferStrategy();

	private Team currentTeam = white;
	
	TextObject fpsCounter = new TextObject(WIDTH-70, HEIGHT-45, 14, "Helvetica", "FPS: ");

	TextObject currentTurn = new TextObject(460, 30, 30, "Helvetica","Current Turn: " + getCurrentTeam().toString());

	public static Team black = new Team("Black");
	public static Team white = new Team("White");

	static Timer whiteTimer = new Timer(1015, 750, 20, white, "Helvetica", null, 10, 0);
	static Timer blackTimer = new Timer(1015, 150, 20, white, "Helvetica", null, 10, 0);

	private static int frames;

	public static ArrayList<ArrayList<Square>> boardList = Square.makeList();

	public RedSquare redSquare = new RedSquare(0, 0);
	public static ArrayList<GreenSquare> greenSquares = new ArrayList<>();

	public PawnMenu pawnMenu = new PawnMenu(100, 100, "images/pawnMenu.png");

	public Game(){
		
		new Window(WIDTH, HEIGHT, "Chess", this);
		
		handler = new Handler();
		input = new Input(this);
		
		this.addMouseListener(input);

		//first coordinate is the column, then the row
		//e.g. boardList.get(0).get(7) gets A8

		//black pieces
		handler.addObject(new Rook(boardList.get(0).get(7), black));
		handler.addObject(new Bishop(boardList.get(1).get(7), black));
		handler.addObject(new Knight(boardList.get(2).get(7), black));
		handler.addObject(new Queen(boardList.get(3).get(7), black));
		handler.addObject(new King(boardList.get(4).get(7), black));
		handler.addObject(new Knight(boardList.get(5).get(7), black));
		handler.addObject(new Bishop(boardList.get(6).get(7), black));
		handler.addObject(new Rook(boardList.get(7).get(7), black));
		handler.addObject(new Pawn(boardList.get(0).get(6), black));
		handler.addObject(new Pawn(boardList.get(1).get(6), black));
		handler.addObject(new Pawn(boardList.get(2).get(6), black));
		handler.addObject(new Pawn(boardList.get(3).get(6), black));
		handler.addObject(new Pawn(boardList.get(4).get(6), black));
		handler.addObject(new Pawn(boardList.get(5).get(6), black));
		handler.addObject(new Pawn(boardList.get(6).get(6), black));
		handler.addObject(new Pawn(boardList.get(7).get(6), black));

		//white pieces
		handler.addObject(new Rook(boardList.get(0).get(0),white));
		handler.addObject(new Bishop(boardList.get(1).get(0), white));
		handler.addObject(new Knight(boardList.get(2).get(0), white));
		handler.addObject(new Queen(boardList.get(3).get(0), white));
		handler.addObject(new King(boardList.get(4).get(0), white));
		handler.addObject(new Knight(boardList.get(5).get(0), white));
		handler.addObject(new Bishop(boardList.get(6).get(0), white));
		handler.addObject(new Rook(boardList.get(7).get(0), white));
		handler.addObject(new Pawn(boardList.get(0).get(1), white));
		handler.addObject(new Pawn(boardList.get(1).get(1), white));
		handler.addObject(new Pawn(boardList.get(2).get(1), white));
		handler.addObject(new Pawn(boardList.get(3).get(1), white));
		handler.addObject(new Pawn(boardList.get(4).get(1), white));
		handler.addObject(new Pawn(boardList.get(5).get(1), white));
		handler.addObject(new Pawn(boardList.get(6).get(1), white));
		handler.addObject(new Pawn(boardList.get(7).get(1), white));

		handler.addObject(fpsCounter);

		handler.addObject(currentTurn);

		handler.addObject(blackTimer);
		handler.addObject(whiteTimer);

		handler.addObject(pawnMenu);

	}
	
	public static void main(String[] args) {

		game = new Game();
		game.run();
		
	}

	public void run() {

		long lastTime = System.nanoTime();//current time in nanoseconds
		double maxFps = 90.0;
		double ns = 1000000000 / maxFps;
		double delta = 0;
		long timer = System.currentTimeMillis();

		while(true){
			long now = System.nanoTime();
			delta += (now - lastTime) / ns;//add the amount of time that has passed divided by ns
			lastTime = now;

			while(delta >= 1){
				tick();
				delta--;
				this.render();
				frames++;
			}

			if(System.currentTimeMillis() - timer > 1000){//if a second has passed
				timer += 1000;
				fpsCounter.setValue("FPS: " + frames);
				frames = 0;
				if(currentTeam == white){
					whiteTimer.increment();
				} else {
					blackTimer.increment();
				}
			}
		}
	}
	
	private static void tick(){
		
		handler.tick();
		
	}
	
	private void render(){
		
		bs = getBufferStrategy();
		
		if(bs == null){
			this.createBufferStrategy(3);
			return;
		}
		
		Graphics g = bs.getDrawGraphics();
		
		g.setColor(Color.black);
		g.fillRect(0, 0, WIDTH, HEIGHT);
		
		g.drawImage(board, (WIDTH-800)/2, (HEIGHT-800)/2, null);

		for(GreenSquare square : greenSquares){
			square.render(g);
		}

		redSquare.render(g);

		handler.render(g);
		
		g.dispose();//releases system resources that g is currently using
		bs.show();
		
	}
	
	private Image getImageFromFile(String path){
		
		Image image = null;
		File file = new File(path);
		
		try{
			image = ImageIO.read(file);
		} catch(IOException e){
			e.printStackTrace();
		}
		
		return image;
		
	}
	
	public Team getCurrentTeam() {
		return currentTeam;
	}

	public void setCurrentTeam(Team team) {
		currentTeam = team;
	}

	public boolean isCheck(){
		for(ArrayList<Square> col: boardList){

			for(Square square : col){

				Piece piece = square.checkSquare();
				if(piece != null && piece.isChecking()){
					System.out.println(piece.getTeam() + " " + piece.getClass());
					return true;
				}

			}

		}
		return false;
	}

	//make a list of all possible moves (valid move to there, and doesn't leave the king in check)
	//if the list is empty, then it is checkmate
	public boolean isCheckmate() {
		ArrayList<Move> validMoves = new ArrayList<>();
		for (GameObject obj : handler.object) {

			if (obj instanceof Piece) {
				Piece piece = (Piece) obj;
				if (piece.getTeam() != getCurrentTeam() && !piece.isDead()) {
					validMoves.addAll(piece.genValidMoves());
				}
			}

		}
		return validMoves.isEmpty();
	}

}
