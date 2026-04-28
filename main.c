#include <stdio.h>
#include <raylib.h>

#define WIDTH 1800
#define HEIGHT 1000

#define cell_size 30


const int cols = WIDTH/cell_size;
const int rows = HEIGHT/cell_size;


struct pixel {
	int posX;
	int posY;
	bool active;
};

const int pix_count = cols * rows;



// PAINTING GRID BLOCK
void paint_grid(struct pixel *pix_grid)
{
	for (int i = 0; i < pix_count; i++)
	{
		if ((pix_grid[i].active) == true)
			DrawRectangle((pix_grid[i]).posX, (pix_grid[i]).posY, cell_size, cell_size, GREEN);
	}
}




// CHECKS IF EVERY PIXEL IS ACTIVE
bool IsAnyPixelActive(struct pixel *pix_grid)
{
	for (int i = 0;i < pix_count; i++)
	{
		if (pix_grid[i].active)
			return true;
	}
	return false;
	
}




// MAIN GAME LOOP
void main_loop(struct pixel *pix_grid, struct pixel *next_pix_grid)
{
	if (IsKeyPressed(KEY_ENTER)){
	//	while (IsAnyPixelActive(pix_grid))
	//	{
			for (int i = 0; i < pix_count; i++)
			{
				int counter = 0;
				// All 8 blocks to check to check
				int E = i + 1;
				int W = i - 1;
				int N = i - cols;
				int NE = N + 1;
				int NW = N - 1;
				int S = i + cols;
				int SW = S - 1;
				int SE = S + 1;
			



				// WHADAP BOIS THIS LOGIC IS WRONG AND I AM LAZY SO DOING A
				// PATCH TO FIX THIS RATHER THEN DOING IT PROPERLY 
				// PEACE TO MY FUTURE SELF
				if (i % cols == cols - 1) {
					E = -1;
					NE = -1;
					SE = -1;
				}
				if (i % cols == 0) {
					W = -1;
					SW = -1;
					NW = -1;
				}
				if (i < rows) { 
					N = -1;
					NE = -1;
					NW = -1;
				}
				if (i > rows * (cols - 1)) {
					S = -1;
					SE = -1;
					SW = -1;
				}




				int direc[] = {NW, N, NE, W, E, SW, S, SE};
				
				for (int j = 0; j < 8; j++)
				{	
					if(direc[j] >= 0 && direc[j] < pix_count) 
					{
						if (pix_grid[direc[j]].active) counter++;
					} 
				}
				
				if (pix_grid[i].active)
				{
					next_pix_grid[i].active = (counter == 2 || counter == 3);
				}
				else 
				{
					next_pix_grid[i].active = (counter == 3);
				}




			// THIS BELOW STUFF IS WRONG
			//	if (counter == 2 || counter == 3)
			//	{
			//		(next_pix_grid[i]).active = true;
			//	}

			}

			for (int i = 0; i < pix_count; i++) pix_grid[i] = next_pix_grid[i];

			for(int i = 0; i < pix_count; i++) (next_pix_grid[i]).active = false;

			
			paint_grid(pix_grid);
	//	}


	}

}




//CHEKCING FOR WHICH GRID BLOCK TO PAINT
void click_loop(struct pixel *pix_grid)
{
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			int mosX = GetMouseX();
			int mosY = GetMouseY();

			int Xoffset = mosX % cell_size;
			int Yoffset = mosY % cell_size;

			mosX -= Xoffset;
			mosY -= Yoffset;

			for (int i = 0; i < pix_count; i++){
				if (((pix_grid[i]).posX == mosX) && ((pix_grid[i]).posY == mosY))
					pix_grid[i].active = true;
			}

		}

	paint_grid(pix_grid);
}




//MAIN LOOP PAINT GRID SCHEMA
int main(int argc, char *argv[])
{
	int used_width = cols * cell_size;
	int used_height = rows * cell_size;
	
	int run = 1;

	
	struct pixel pix_grid[pix_count]; 
	struct pixel next_pix_grid[pix_count];

	InitWindow(WIDTH, HEIGHT, "Cellular Automata");

	while(!WindowShouldClose())
	{
	BeginDrawing();

	ClearBackground(BLACK);


	for(int y = 0;y < rows; y++)
	{
		for(int x = 0; x < cols; x++)
		{
			int posX =  x * cell_size;
			int posY = y * cell_size;
			
			int which_pix = y * cols + x;

			(pix_grid[which_pix]).posX = posX;
			(pix_grid[which_pix]).posY = posY;
			if (run==1) (pix_grid[which_pix]).active = false;

		}
	}
	run++;

	for(int i = 0; i < pix_count; i++)
	{
		next_pix_grid[i] = pix_grid[i];	
	}

	for(int i = 0; i < pix_count; i++) (next_pix_grid[i]).active = false;


	for(int i = 0; i < pix_count; i++){
		DrawRectangleLines((pix_grid[i]).posX, (pix_grid[i]).posY, cell_size, cell_size, GREEN);
	}
	
	click_loop(pix_grid); 

	main_loop(pix_grid, next_pix_grid);



	EndDrawing();
	}



	return 0;
}
