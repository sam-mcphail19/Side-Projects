package main;

public class Timer extends TextObject {

    int minutes;
    int seconds;
    boolean stopped = false;
    Team team;

    public Timer(int x, int y, int fontSize, Team team, String font, String value, int minutes, int seconds) {

        super(x, y, fontSize, font, value);
        this.team = team;
        this.minutes = minutes;
        this.seconds = seconds;
        this.value = Integer.toString(minutes) + ":" + String.format("%02d", seconds);

    }

    public void increment(){
        if(stopped){
            return;
        }


        seconds -= 1;
        if(seconds < 0){
            minutes -= 1;
            if(minutes < 0){
                minutes = 0;
                seconds = 0;
                this.value = Integer.toString(minutes) + ":" + String.format("%02d", seconds);
                return;
            }
            seconds = 59;
        }

        this.value = Integer.toString(minutes) + ":" + String.format("%02d", seconds);

    }

    public void setStopped(boolean stopped){
        this.stopped = stopped;
    }

}
