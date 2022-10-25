#include "raylib.h"
//structure that contains variales for the ball

struct Ball{
    float x,y;
    float speedx,speedy;
    float radius;
};

//structure that contains variables for the paddle

struct Paddle{
  float x,y;
  float speed;
  float width,height;
};

//function to return a rectangular object 

Rectangle getRect(float x,float y,float width,float height){
    struct Rectangle rectangle;
    rectangle.x = x - width/2;
    rectangle.y = y - height/2;
    rectangle.height =height;
    rectangle.width = width;
    return rectangle;
}

int main(){
   //opening a window
    InitWindow(800,600,"Pong");
    SetWindowState(FLAG_VSYNC_HINT);

    //ball variables
    struct Ball ball;
    ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedx = 300;
	ball.speedy = 300;

    //left Paddle variables

    struct Paddle lp;
    lp.x = 50;
	lp.y = GetScreenHeight() / 2;
	lp.width = 10;
	lp.height = 100;
	lp.speed = 600;

    //Right paddle variables

    struct Paddle rp;
    rp.x = GetScreenWidth() - 50;
	rp.y = GetScreenHeight() / 2;
	rp.width = 10;
	rp.height = 100;
	rp.speed = 600;

    const char* winnerText = false;
    
    while(!WindowShouldClose()){

        //moving the ball
        
        ball.x += ball.speedx * GetFrameTime();
        ball.y += ball.speedy * GetFrameTime();

        //Ball stays withing the vertical bounds  
        if(ball.y<=0){
            ball.y =0;
            ball.speedy*= -1;
        }
        if(ball.y>=GetScreenHeight()){
            ball.y = GetScreenHeight();
            ball.speedy *=-1;
        }
        //moving the left and the right paddles based on the key pressed 
        if(IsKeyDown(KEY_W)){
            if(lp.y < 0.0f ){
                lp.y =0;
            }
            else{
                lp.y -= lp.speed * GetFrameTime();
            }
        }
        if(IsKeyDown(KEY_S)){
            if(lp.y > GetScreenHeight() ){
                lp.y =GetScreenHeight();
            }
            else{
                lp.y += lp.speed * GetFrameTime();
            }
        }
        if(IsKeyDown(KEY_UP)){
           if(rp.y < 0.0f ){
                rp.y =0;
            }
            else{
                rp.y -= rp.speed * GetFrameTime();
            }
        }
        if(IsKeyDown(KEY_DOWN)){
            if(rp.y > GetScreenHeight() ){
                rp.y =GetScreenHeight();
            }
            else{
                rp.y += rp.speed * GetFrameTime();
            }
        }


        //vector2 struct initialization for checking collision
        Vector2 BALL;
        BALL.x = ball.x;
        BALL.y = ball.y;
        //checking the collision between the paddle and the ball
        if(CheckCollisionCircleRec( BALL,ball.radius,getRect(lp.x,lp.y,lp.width,lp.height))){
           if (ball.speedx < 0)
			{
				ball.speedx *= -1.1f;
				ball.speedy = (ball.y - lp.y) / (lp.height / 2) * ball.speedx;
			}
        }
        if(CheckCollisionCircleRec( BALL,ball.radius,getRect(rp.x,rp.y,rp.width,rp.height))){
            if (ball.speedx > 0)
			{
				ball.speedx *= -1.1f;
				ball.speedy = (ball.y - rp.y) / (rp.height / 2) * -ball.speedx;
			}
        }
        //Win condition for the game
        if(ball.x < 0){
            winnerText ="Right player wins!";
        }
        if(ball.x>GetScreenWidth()){
            winnerText = "Left player wins!";
        }
        //restarting the game condition 
        if(winnerText && IsKeyPressed(KEY_SPACE)){
            ball.x = GetScreenWidth()/2;
            ball.y = GetScreenHeight()/2;
            ball.speedx = 300;
            ball.speedy = 300;
            winnerText = false;

        }
        //Drawing objects on the window.
        BeginDrawing();
            ClearBackground(BLACK);
            //Circle drawing 

            DrawCircle(ball.x,ball.y,ball.radius,YELLOW);
            
            //left paddle drawing
            
            DrawRectangle(lp.x - lp.width / 2, lp.y - lp.height / 2, 10, 100,RED);
            
            //right paddle drawing 
            
            DrawRectangle(rp.x - rp.width / 2, rp.y - rp.height / 2, 10, 100, RED);

            if(winnerText){
                int spaceTextWidth = MeasureText("Enter space to restart!",30);
                int textWidth = MeasureText(winnerText,60);
                DrawText("Enter space to restart!",GetScreenWidth()/2 - spaceTextWidth/2,10,30,ORANGE);
                DrawText(winnerText,GetScreenWidth()/2 -textWidth/2,GetScreenHeight()/2 -30,60,VIOLET);
            }

            DrawFPS(10,10);
        EndDrawing();
    }
    //closing a window
    CloseWindow();
}