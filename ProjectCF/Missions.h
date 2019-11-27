#pragma once
/*						H								J
=	A				=       =
=			 ========================================			=
=	L		 =		=		=		=		=		=			=
=			 =		=		=		=		=		=			=
=			=========================================			=
=			  =		=		=		=		=		=			=
=	G		  =		=		=		=		=		=			=
=			=========================================			=
=			 =		=		=		=		=		=			=
=			 =		=		=		=		=		=			=
=			 =========================================			=
=			 =		=		=		=		=		=  			=
=			 =		=		=		=		=		=			=
=			 ========================================= 			=
=			 =		=		=		=		=		=			=
=			 =		=		=		=		=		=			=
=	B		 ======================================== I			=
  =	        		 				=		=					=
	=								C		D		E	   K  	=

	F
		================================================
		D
*/


#define Ms_Pos_A  20
#define Ms_Pos_B 210
#define Ms_Pos_C 150
#define Ms_Pos_D 185
#define Ms_Pos_E 217
#define Ms_Pos_F 10
#define Ms_Pos_G 88
#define Ms_Pos_H 90
#define Ms_Pos_I 240        
#define Ms_Pos_J 10
#define Ms_Pos_K 240
#define Ms_Pos_L 57

void CollectGoods_GotoGoods ();
void CollectGoods_CatchBall ();
void CollectGoods_GetballBack ();
void CollectGoods_DropBall ();

void MainTask_CollectGoods ();
void MainTask_EasyMaze (); 
void MainTask_SavePeople ();
