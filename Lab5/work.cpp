#include<stdio.h>
#include<Windows.h>
#include<conio.h>
void draw_ship(int,int);
void gotoxy(int,int);
void erase_ship(int,int);
void setcursor(bool);
void setcolor(int, int);
void draw_shot(int, int);
void erase_shot(int, int);

int main() {
	int x = 38, y = 20, position_x[5],position_y[5],shot[5];
	char ch = ' ';
	setcursor(0);

	draw_ship(x, y); 
	for (int i = 0; i < 5; i++) {
		shot[i] = 0;		//กำหนดค่าของกระสุนไว้ ไม่ให้เป็นค่าขยะเฉยๆ	
	}

	do {
		if (_kbhit()) {
			ch = _getch();
		base1 :	if (ch == 'a' && x > 0) {
				do {	// วิ่งซ้ายเรื่อยๆ จนกว่าจะชนหรือกด s
					erase_ship(x, y);
					draw_ship(--x, y); //ให้ขยับไปทางซ้าย		
					Sleep(100);
					if (_kbhit()) {     // รับค่าคีบิดอีกครั้งนึง
						ch = _getch();
					}
					if (ch == 'd') { goto base2; }  //เข้าไปทำ b
				}while (x > 0 && ch != 's');   //เจอ s จะหยุด
			}


		base2 :	if (ch == 'd' && x < 73) {
				do {
					erase_ship(x, y);	//ให้ขยับไปทางขวา
					draw_ship(++x, y);
					Sleep(100);
					if (_kbhit()) {
						ch = _getch();
					}
					if (ch == 'a') { goto base1; }  //เข้าไปทำ a
				} while (x < 73 && ch != 's' );
			}

		
			if (ch == 'w'&& y>0) {
				erase_ship(x, y);	//ให้ขยับขึ้นบน
				draw_ship(x, --y);
	
			} 

						
			if (ch == ' ') {   // กด spacbar เพิ้อ ยิงกระสุน

				for (int i = 0;i<5;i++) {
					if(shot[i]==0){			// งงงงงงงงงงงงงงงงงงงงงงงงงงงงงงงงงงงง
					
						shot[i] = 1;
						position_x[i] = x;  // ค่า x เป็นค่าของยาน เลยเป็นยานออกมา
						position_y[i] = y - 2;
						draw_shot(position_x[i], position_y[i] );
						break;
						
					} 
				}
			}


				/*		if (ch == 's'&& y<24) {
							erase_ship(x, y);	//ให้ขยับลงล่าง
							draw_ship(x, ++y);

						}
				*/
			
			fflush(stdin);
		}

		for (int i = 0; i < 5; i++) {
			if (shot[i] == 1)    //เปิดค่าให้มันยิงมา
			{

				erase_shot(position_x[i], position_y[i]);
				position_y[i] = position_y[i] - 1;
				if (position_y[i] > 0) {     //เป็นการฟิคขอบเขตของความสูงของจอภาพ
					draw_shot(position_x[i], position_y[i]);
				}				
				else
				{
					shot[i] = 0;
				}
			}
		}

		Sleep(100);		

	} while (ch != 'x');  setcolor(7, 0);


	return 0;
}



void gotoxy(int x, int y) {    // ตน. ของยาน
	COORD c = { x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x,int y) {
	setcursor(0);
	gotoxy(x, y);
	setcolor(2, 4);  // เปลี่ยนสีก่อนเริ่มเดิน
	printf("<-0->"); 
	
}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("      ");
}

void setcursor(bool visible) {
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void erase_shot(int x, int y) {		//ลบรูปกระสุน
	gotoxy(x, y);
	setcolor(0, 0);
	printf("      ");

}

void draw_shot(int x, int y) {		//วาดรูปกระสุน
	gotoxy(x,y);
	setcolor(7, 0);
	printf("  A ");
}





/*


#include<stdio.h>
#include<Windows.h>
#include<conio.h>
void draw_ship(int,int);
void gotoxy(int,int);
void erase_ship(int,int);
void setcursor(bool);
void setcolor(int, int);
void erase_space(int, int);

int main() {

	char ch = ' ';
	int x = 38, y = 20;
	draw_ship(x, y);
	setcursor(0);
	setcolor(0, 0);  //(สีตัวอักษร,สีพื้นหลัง)
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0) {
				draw_ship(--x, y); //ให้ขยับไปทางซ้าย
				erase_space(0, 0);
			}
			if (ch == 'd' && x < 73) {
				erase_ship(x, y);	//ให้ขยับไปทางขวา
				draw_ship(++x, y);
				erase_space(0, 0);
			}
			if (ch == 'w'&& y>0) {
				erase_ship(x, y);	//ให้ขยับขึ้นบน
				draw_ship(x, --y);
				erase_space(0, 0);
			}
			if (ch == 's'&& y<24) {
				erase_ship(x, y);	//ให้ขยับลงล่าง
				draw_ship(x, ++y);
				erase_space(0, 0);
			}

			fflush(stdin);
		}
		Sleep(100);

	} while (ch != 'x');  setcolor(7, 0);


	return 0;
}



void gotoxy(int x, int y) {
	COORD c = { x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x,int y) {
	gotoxy(x, y);
	setcolor(2, 4);  // เปลี่ยนสีก่อนเริ่มเดิน
	printf("<-0-> ");

}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	printf("      ");
}

void erase_space(int x, int y) {
	setcolor(x, y);   // ทำให้ข้ความ return0 หาย
	printf("      ");
}


void setcursor(bool visible) {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}



*/