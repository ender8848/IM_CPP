#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

#include "river.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new (nothrow) char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new (nothrow) char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* pre-supplied function which creates an empty ASCII-art scene */
char **create_scene() {
  char **scene = allocate_2D_array(SCENE_HEIGHT, SCENE_WIDTH);

  for (int i=0; i<SCENE_HEIGHT; i++) 
    for (int j=0; j<SCENE_WIDTH; j++)
      scene[i][j] = ' ';

  return scene;
}

/* pre-supplied function which frees up memory allocated for an ASCII-art scene */
void destroy_scene(char **scene) {
  deallocate_2D_array(scene, SCENE_HEIGHT);
}

/* pre-supplied function which displays an ASCII-art scene */
void print_scene(char **scene) {
  for (int i=0; i<SCENE_HEIGHT; i++) {
    for (int j=0; j<SCENE_WIDTH; j++)
      cout << scene[i][j];
    cout << endl;
  }
}

/* helper function which removes carriage returns and newlines from strings */
void filter(char *line) {
  while (*line) {
    if (*line >= ' ')
      line++;
    else 
      *line = '\0';
  }
}

/* pre-supplied function which inserts an ASCII-art drawing stored in a file
   into a given ASCII-art scene starting at coordinates (row,col)  */
bool add_to_scene(char **scene, int row, int col, const char *filename) {

  ifstream in(filename);
  if (!in)
    return false;

  int start_col = col;
  char line[512];
  in.getline(line,512);
  filter(line);
  while (!in.fail()) {
    for (size_t n=0; n<strlen(line); n++) {
      if (row >= SCENE_HEIGHT)
	return false;
      if (col >= SCENE_WIDTH)
	break;
      scene[row][col++] = line[n];
    }
    row++;
    col = start_col;
    in.getline(line,512);
    filter(line);
  }
  return true;
}

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code) {
  switch(code) {
  case ERROR_INVALID_CANNIBAL_COUNT:
    return "Invalid cannibal count";
  case ERROR_INVALID_MISSIONARY_COUNT:
    return "Invalid missionary count";
  case ERROR_INVALID_MOVE:
    return "Invalid move";
  case ERROR_MISSIONARIES_EATEN:
    return "The missionaries have been eaten! Oh dear!";
  case ERROR_INPUT_STREAM_ERROR:
    return "Unexpected input stream error";
  case ERROR_BONUS_NO_SOLUTION:
    return "No solution";
  case VALID_GOAL_STATE:
    return "Problem solved!";
  case VALID_NONGOAL_STATE:
    return "Valid state, everything is OK!";
  }
  return "Unknown error";
}


/* insert your functions here */

void draw_person_on_boat(char** scene, size_t row, size_t col, std::string const& boat) {
  size_t m_num = count(boat.begin(), boat.end(), 'M');
  size_t c_num = count(boat.begin(), boat.end(), 'C');
  for (size_t i = 0; i < m_num; ++i) {
    add_to_scene(scene, row, col, "missionary.txt");
    col += 6;
  } 
  for (size_t i = 0; i < c_num; ++i) {
    add_to_scene(scene, row, col, "cannibal.txt");
    col += 5;
  } 
}


char** make_river_scene(std::string const& left, std::string const& boat) {
  size_t leftC, leftM, rightC, rightM, boatM, boatC;
  // char boat_stuff[BOATSIZE] = {};
  bool boat_on_left;
  char **scene = create_scene();
  add_to_scene(scene, 0, 0, "bank.txt");
  add_to_scene(scene, 0, 53, "bank.txt");
  add_to_scene(scene, 3, 30, "sun.txt");
  add_to_scene(scene, 19, 19, "river.txt");
  leftC = count(left.begin(), left.end(), 'C');
  leftM = count(left.begin(), left.end(), 'M');
  boat_on_left = static_cast<bool>(count(left.begin(), left.end(), 'B'));
  boatC = count(boat.begin(), boat.end(), 'C');
  boatM = count(boat.begin(), boat.end(), 'M');
  rightC = BANKSIZE - leftC - boatC;
  rightM = BANKSIZE - leftM - boatM;
  // draw C and M in left bank
  for (size_t i = 0; i < leftM; ++i) {
    add_to_scene(scene, 2, i*6+1, "missionary.txt");
  }
  for (size_t i = 0; i < leftC; ++i) {
    add_to_scene(scene, 11, i*6+1, "cannibal.txt");
  }
  // draw C and M in right bank
  for (size_t i = 0; i < rightM; ++i) {
    add_to_scene(scene, 2, i*6+54, "missionary.txt");
  }
  for (size_t i = 0; i < rightC; ++i) {
    add_to_scene(scene, 11, i*6+54, "cannibal.txt");
  }
  // locate boat and draw persons on boat
  if (boat_on_left) {
    add_to_scene(scene, 17, 19, "boat.txt");
    draw_person_on_boat(scene, 17-HEIGHT, 19+DIS, boat);
  }
  else {
    add_to_scene(scene, 17, 36, "boat.txt");
    draw_person_on_boat(scene, 17-HEIGHT, 36+DIS, boat);
  }

  return scene;
}


bool valid_move(std::string left, std::string const& targets, Status& status) {
  size_t m_num_left = count(left.begin(), left.end(), 'M');
  size_t c_num_left = count(left.begin(), left.end(), 'C');
  size_t m_num_boat = count(targets.begin(), targets.end(), 'M');
  size_t c_num_boat = count(targets.begin(), targets.end(), 'C');
  if (m_num_left + m_num_boat > 3) {
    status = ERROR_INVALID_MISSIONARY_COUNT;
    return false;
  }
  if (c_num_left + c_num_boat > 3) {
    status = ERROR_INVALID_CANNIBAL_COUNT;
    return false;
  }
  if (targets.length() == 0 || targets.length() > 2) {
    status = ERROR_INVALID_MOVE;
    return false;
  }
  for (char ch : targets) {
    if (ch != 'M' && ch != 'C') {
      status = ERROR_INVALID_MOVE;
      return false;
    }
  }
  return true;
}


Status perform_crossing(char* left, std::string const& targets) {
  bool boat_on_left = strstr(left, "B"); 
  Status status;
  // left_ stores the left bank situation after a move
  string left_(left);
  // check if targets(boat) is valid
  if (!valid_move("", targets, status)) {return status;}
  // store some data of original left condition
  size_t m_num = count(left_.begin(), left_.end(), 'M');
  size_t c_num = count(left_.begin(), left_.end(), 'C');
  size_t m_num_after, c_num_after;
  if (boat_on_left) {
    m_num_after = m_num - count(targets.begin(), targets.end(), 'M');
    c_num_after = c_num - count(targets.begin(), targets.end(), 'C');
  }
  else {
    m_num_after = m_num + count(targets.begin(), targets.end(), 'M');
    c_num_after = c_num + count(targets.begin(), targets.end(), 'C');
  }
  // generate left_ in loading situation
  left_ = "";
  if (boat_on_left) {
    for (size_t i = 0; i < m_num_after; ++i) {left_ += "M";}
    for (size_t i = 0; i < c_num_after; ++i) {left_ += "C";}
    left_ += "B";
  }
  else {
    for (size_t i = 0; i < m_num; ++i) {left_ += "M";}
    for (size_t i = 0; i < c_num; ++i) {left_ += "C";}
  }
  // check if a move is valid according to current left_ and targets
  if (!valid_move(left_, targets, status)) {return status;}

  // 1. draw the initial graph
  cout << "Loading the boat..." << endl;
  char** scene = make_river_scene(left_,targets);
  print_scene(scene);
  destroy_scene(scene);
  scene = nullptr;
  // modify left_, change the 'B'
  if (count(left_.begin(), left_.end(), 'B')) {left_.erase(left_.length()-1, 1);}
  else {left_ += 'B';}
  // 2. cross river
  cout << "Crossing river..." << endl;
  scene = make_river_scene(left_,targets);
  print_scene(scene);
  destroy_scene(scene);
  scene = nullptr;
  // change left_, add left_ with B is boat runs from right side
  if (!boat_on_left) {left_ += targets;}
  // 3. Unloading the boat...
  cout << "Unloading the boat..." << endl;
  scene = make_river_scene(left_,"");
  print_scene(scene);
  destroy_scene(scene);
  scene = nullptr;
  
  strcpy(left, left_.c_str());
  
  // carefully think about safe condition
  if (c_num_after != m_num_after && m_num_after && (BANKSIZE - m_num_after)) {return ERROR_MISSIONARIES_EATEN;}
  // valid but non-goal
  if (count(left_.begin(), left_.end(), 'M') + count(left_.begin(), left_.end(), 'C') == 0) {
    return VALID_GOAL_STATE;
  }
  else {return VALID_NONGOAL_STATE;}
}


Status play_game() {
  cout << "Welcome to the river game!\n\n";
  cout << "The puzzle concerns three missionaries and three cannibals who must cross a river\n";
  cout <<  "from the left bank to the right bank using a boat which carries at most two people.\n";
  cout <<  "The boat cannot cross the river by itself with noone on board.\n";
  cout <<  "Swimming is impossible since the river contains piranhas and sharks\n\n";
  cout << "For both banks, if there are missionaries present on a bank, \n";
  cout << "then there must not be more cannibals than missionaries on that bank\n";
  cout << "(since then the cannibals eat the missionaries).\n\n";
  string play;
  Status result;
  char left[10] = "MMMCCCB";
  cout << " Initial condition is like this: \n";
  char** scene = make_river_scene("MMMCCCB","");
  print_scene(scene);  
  destroy_scene(scene);
  cout << "what to move? (MM/MC/CC/C/M): \n";
  while (getline(cin, play, '\n')) {
    result = perform_crossing(left, play);
    if (result == ERROR_INVALID_MOVE) {
      cout << "Invalid move. please try again.\n";
      continue;
    }
    if (result == ERROR_INVALID_CANNIBAL_COUNT) {
      cout << "Too many cannibals now. please try again.\n";
      continue;
    }
    if (result == ERROR_INVALID_MISSIONARY_COUNT) {
      cout << "Too many missionaries now. please try again.\n";
      continue;
    }
    else if(result == ERROR_MISSIONARIES_EATEN) {
      // draw a pot aha
      cout << "Breakfast time!" << endl;
      char **scene = create_scene();
      add_to_scene(scene, 2, 24, "sun.txt");
      add_to_scene(scene,14, 45, "cannibal.txt");
      add_to_scene(scene,14,  9, "cannibal.txt");
      add_to_scene(scene, 8, 25, "missionary.txt");
      add_to_scene(scene, 8, 30, "missionary.txt");
      add_to_scene(scene, 12, 20, "pot.txt");
      print_scene(scene);
      destroy_scene(scene);
      break;
    }
    else if(result == VALID_GOAL_STATE) {break;}
    else{cout << "what to move? (MM/MC/CC/C/M): \n";}
  }
  return result;
}