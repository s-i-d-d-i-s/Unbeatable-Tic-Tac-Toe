#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

char grid[3][3];


void reset_board(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            grid[i][j]='.';
        }
    }
}

void display_board(){
    cout << " ___________"<<endl;
    cout << "| "<<grid[0][0]<<" | "<<grid[0][1]<<" | "<<grid[0][2]<<" |";
    cout << endl;
    cout << " ___________"<<endl;
    cout << "| "<<grid[1][0]<<" | "<<grid[1][1]<<" | "<<grid[1][2]<<" |";
    cout << endl;
    cout << " ___________"<<endl;
    cout << "| "<<grid[2][0]<<" | "<<grid[2][1]<<" | "<<grid[2][2]<<" |";
    cout << endl;
    cout << " ----------"<<endl;
}

void show_win(int player){
    if(player==1){
        for(int i=0;i<3;i++){
            if(grid[i][0]=='X' and grid[i][1]=='X' and grid[i][2]=='X'){
                grid[i][0]='*';
                grid[i][1]='*';
                grid[i][2]='*';
            }
        }
        for(int i=0;i<3;i++){
            if(grid[0][i]=='X' and grid[1][i]=='X' and grid[2][i]=='X'){
                grid[0][i]='*';
                grid[1][i]='*';
                grid[2][i]='*';
            }
        }

        if(grid[0][0]=='X' and grid[1][1]=='X' and grid[2][2]=='X'){
            for(int i=0;i<3;i++){
                grid[i][i]='*';
            }
        }
        if(grid[0][2]=='X' and grid[1][1]=='X' and grid[2][0]=='X'){
            for(int i=0;i<3;i++){
                grid[i][2-i]='*';
            }
        }
    }else{
        for(int i=0;i<3;i++){
            if(grid[i][0]=='O' and grid[i][1]=='O' and grid[i][2]=='O'){
                grid[i][0]='*';
                grid[i][1]='*';
                grid[i][2]='*';
            }
        }
        for(int i=0;i<3;i++){
            if(grid[0][i]=='O' and grid[1][i]=='O' and grid[2][i]=='O'){
                grid[0][i]='*';
                grid[1][i]='*';
                grid[2][i]='*';
            }
        }

        if(grid[0][0]=='O' and grid[1][1]=='O' and grid[2][2]=='O'){
            for(int i=0;i<3;i++){
                grid[i][i]='*';
            }
        }
        if(grid[0][2]=='O' and grid[1][1]=='O' and grid[2][0]=='O'){
            for(int i=0;i<3;i++){
                grid[i][2-i]='*';
            }
        }
    }
}
void make_move(int player,int x,int y){
    if(player==0){
        grid[x][y]='O';
    }else{
        grid[x][y]='X';
    }
}

void undo_make_move(int x,int y){
    grid[x][y]='.';
}

bool check_win(int player){
    if(player==1){
        for(int i=0;i<3;i++)
            if(grid[i][0]=='X' and grid[i][1]=='X' and grid[i][2]=='X') return true;
        for(int i=0;i<3;i++)
            if(grid[0][i]=='X' and grid[1][i]=='X' and grid[2][i]=='X') return true;
        if(grid[0][0]=='X' and grid[1][1]=='X' and grid[2][2]=='X')return true;
        if(grid[0][2]=='X' and grid[1][1]=='X' and grid[2][0]=='X')return true;
        return false;
    }else{
        for(int i=0;i<3;i++)
            if(grid[i][0]=='O' and grid[i][1]=='O' and grid[i][2]=='O') return true;
        for(int i=0;i<3;i++)
            if(grid[0][i]=='O' and grid[1][i]=='O' and grid[2][i]=='O') return true;
        if(grid[0][0]=='O' and grid[1][1]=='O' and grid[2][2]=='O')return true;
        if(grid[0][2]=='O' and grid[1][1]=='O' and grid[2][0]=='O')return true;
        return false;
    }
}



pair<double,pair<int,int>> solve(int player,int depth){
    if(check_win(player^1)){
        return {0,{-1,-1}};
    }

    vector<pair<double,pair<int,int>>> poss;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(grid[i][j]=='.'){
                make_move(player,i,j);
                pair<double,pair<int,int>> temp = solve(player^1,depth+1);
                undo_make_move(i,j);
                poss.push_back({100-temp.first,{i,j}});
            }
        }
    }

    if(poss.size()==0){
        return {50,{-1,-1}};
    }
    sort(poss.begin(),poss.end());
    return poss.back();
}




void make_random_move(int player){
    vector<pair<int,int>> v;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(grid[i][j]=='.'){
                v.push_back({i,j});
            }
        }
    }
    if(v.size()==0){
        cout << "Game Draw !" << endl;
        exit(0);
    }
    random_shuffle(v.begin(),v.end());
    pair<int,int> temp = v[v.size()/2];

    if(player==1){
        grid[temp.first][temp.second]='X';
    }else{
        grid[temp.first][temp.second]='O';
    }
}

bool check_draw(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(grid[i][j]=='.')return false;
        }
    }
    return true;
}


void play_as(int player,bool reset){
    if(reset)
        reset_board();
    while(true){
        system("clear");
        if(check_draw()){
            cout << "Game Draw !" << endl;
            exit(0);
        }
        int choice;
        if(player==1){
            cout << "Player "<< player << " turn"<<endl;
            display_board();
            cout << "Enter 0 to end game" << endl;
            cout << "Enter 1 to make a move" << endl;
            cin >> choice;
        }
        if(choice==0){
            return ;
        }else if(choice==1){
            if(player==1){
                cout << "Enter (x,y) of the cell you want to place your mark !" << endl;
                int x,y;
                cin >> x >> y;
                x--;
                y--;

                if(x>=0 and x<=2 and y>=0 and y<=2 and grid[x][y]=='.'){
                    make_move(player,x,y);
                    if(check_win(player)){
                        system("clear");
                        display_board();
                        cout << endl;
                        show_win(player);
                        display_board();
                        cout << "Player " << player << " Wins !" << endl;
                        exit(0);
                    }
                }else{
                    cout << "Enter a valid cell !\nPress Any Key To Continue" << endl;
                    getchar();
                    getchar();
                }
            }else{
                pair<double,pair<int,int>> temp = solve(player,0);
                if(temp.first==0){
                    make_random_move(player);
                }else{
                    make_move(player,temp.second.first,temp.second.second);
                }
                if(check_win(player)){
                    system("clear");
                    display_board();
                    cout << endl;
                    show_win(player);
                    display_board();
                    cout << "Player " << (player)<< " Wins !" << endl;
                    exit(0);
                }
            }
            player^=1;
        }else{
            cout << "Enter a valid option !\nPress Any Key To Continue" << endl;
            getchar();
            getchar();
        }
    }
    return ;
}


void play_game(){
    int choice;
    reset_board();
    while(true){
        system("clear");
        cout << "Enter 0 to go back" << endl;
        cout << "Enter 1 to play first" << endl;
        cout << "Enter 2 to play second" << endl;
        cin >> choice;

        int player=1;
        if(choice==0){
            return;
        }else if(choice==1){
            play_as(player,true);
        }else if(choice==2){
            make_random_move(player^1);
            play_as(player,false);
        }else{
            cout << "Enter a valid option !\nPress Any Key To Continue" << endl;
            getchar();
            getchar();
        }

    }
}

int main() {
    srand(time(NULL));
    int choice;
    while(true){
        system("clear");
        cout << "Enter 0 to Quit" << endl;
        cout << "Enter 1 to Start Game" << endl;
        cin >> choice;

        if(choice==0){
            exit(0);
        }else if(choice==1){
            play_game();
        }else{
            cout << "Enter a valid option !\nPress Any Key To Continue" << endl;
            getchar();
            getchar();
        }

    }

    return 0;
}
