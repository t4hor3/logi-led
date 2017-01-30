#include <map>
#include <vector>
#include <fstream>
#include "classes/Keyboard.h"

using namespace std;

void usage() {
	string appname = "g810-led";
	cout<<appname<<" Usages :\n";
	cout<<"-----------------\n";
	cout<<"\n";
	cout<<"  -s  effect :\t\t\tSet keyboard startup effect\n";
	cout<<"\n";
	cout<<"  -a  color :\t\t\tSet all keys\n";
	cout<<"  -g  group, color :\t\tSet a group of keys\n";
	cout<<"  -k  key, color :\t\tSet a key\n";
	cout<<"\n";
	cout<<"  -an color :\t\t\tSet all keys without commit\n";
	cout<<"  -gn group, color :\t\tSet a group of keys without commit\n";
	cout<<"  -kn key, color :\t\tSet a key without commit\n";
	cout<<"\n";
	cout<<"  -c :\t\t\t\tCommit changes\n";
	cout<<"\n";
	cout<<"  -fx-color color :\t\tSet static color effect\n";
	cout<<"  -fx-breathing color, speed :\tSet breathing effect\n";
	cout<<"  -fx-cycle speed :\t\tSet color cycle effect\n";
	cout<<"  -fx-hwave speed :\t\tSet horizontal color wave effect\n";
	cout<<"  -fx-vwave speed :\t\tSet vertical color wave effect\n";
	cout<<"  -fx-cwave speed :\t\tSet center color wave effect\n";
	cout<<"\n";
	cout<<"  -p  profilefile :\t\tLoad a profile\n";
	cout<<"\n";
	cout<<"  -h | --help :\t\t\tthis help message\n";
	cout<<"  -lk | --list-keys :\t\tList keys in groups\n";
	cout<<"\n";
	cout<<"color formats :\t\t\tRRGGBB (hex value for red, green and blue)\n";
	cout<<"speed formats :\t\t\tSS (hex value for speed)\n";
	cout<<"\n";
	cout<<"effect values :\t\t\trainbow, color\n";
	cout<<"key values :\t\t\tabc... 123... and other\n";
	cout<<"group values :\t\t\tlogo, indicators, fkeys, modifiers, multimedia, arrows, numeric, functions, keys, gkeys\n";
	cout<<"\n";
	cout<<"sample :\n";
	cout<<appname<<" -k logo ff0000\n";
	cout<<appname<<" -a 00ff00\n";
	cout<<appname<<" -g fkeys ff00ff\n";
	cout<<appname<<" -s color\n";
	cout<<appname<<" -fx-cycle 10\n";
}

void listkeys() {
	string appname = "g810-led";
	cout<<appname<<" Keys in groups :\n";
	cout<<"-------------------------\n";
	cout<<"\n";
	cout<<"Group logo :\n";
	cout<<" logo\n";
	cout<<" logo2\n";
	cout<<"\n";
	cout<<"Group indicators :\n";
	cout<<" num_indicator, numindicator, num\n";
	cout<<" caps_indicator, capsindicator, caps\n";
	cout<<" scroll_indicator, scrollindicator, scroll\n";
	cout<<" game_mode, gamemode, game\n";
	cout<<" back_light, backlight, light\n";
	cout<<"\n";
	cout<<"Group fkeys :\n";
	cout<<" f1 - f12\n";
	cout<<"\n";
	cout<<"Group modifiers :\n";
	cout<<" shift_left, shiftleft, shiftl\n";
	cout<<" ctrl_left, ctrlleft, ctrll\n";
	cout<<" win_left, winleft, win_left\n";
	cout<<" alt_left, altleft, altl\n";
	cout<<" alt_right, altright, altr, altgr\n";
	cout<<" win_right, winright, winr\n";
	cout<<" menu\n";
	cout<<" ctrl_right, ctrlright, ctrlr\n";
	cout<<" shift_right, shiftright, shiftr\n";
	cout<<"\n";
	cout<<"Group multimedia :\n";
	cout<<" mute\n";
	cout<<" play_pause, playpause, play\n";
	cout<<" stop\n";
	cout<<" previous, prev\n";
	cout<<" next\n";
	cout<<"\n";
	cout<<"Group arrows :\n";
	cout<<" arrow_top, arrowtop, top\n";
	cout<<" arrow_left, arrowleft, left\n";
	cout<<" arrow_bottom, arrowbottom, bottom\n";
	cout<<" arrow_right, arrowright, right\n";
	cout<<"\n";
	cout<<"Group numeric :\n";
	cout<<" num_lock, numlock\n";
	cout<<" num_slash, numslash, num/\n";
	cout<<" num_asterisk, numasterisk, num*\n";
	cout<<" num_minus, numminus, num-\n";
	cout<<" num_plus, numplus, num+\n";
	cout<<" numenter\n";
	cout<<" num0 - num9\n";
	cout<<" num_dot, numdot, num.\n";
	cout<<"\n";
	cout<<"Group functions :\n";
	cout<<" escape, esc\n";
	cout<<" print_screen, printscreen, printscr\n";
	cout<<" scroll_lock, scrolllock\n";
	cout<<" pause_break, pausebreak\n";
	cout<<" insert, ins\n";
	cout<<" home\n";
	cout<<" page_up, pageup\n";
	cout<<" delete, del\n";
	cout<<" end\n";
	cout<<" page_down, pagedown\n";
	cout<<"\n";
	cout<<"Group keys :\n";
	cout<<" 0 - 9\n";
	cout<<" a - z\n";
	cout<<" tab\n";
	cout<<" caps_lock, capslock\n";
	cout<<" space\n";
	cout<<" backspace, back\n";
	cout<<" enter\n";
	cout<<" tilde\n";
	cout<<" minus\n";
	cout<<" equal\n";
	cout<<" open_bracket\n";
	cout<<" close_bracket\n";
	cout<<" backslash\n";
	cout<<" semicolon\n";
	cout<<" dollar\n";
	cout<<" quote\n";
	cout<<" intl_backslash\n";
	cout<<" comma\n";
	cout<<" period\n";
	cout<<" slash\n";
	cout<<"Group gkeys :\n";
	cout<<" g1 - g9\n";
}

int commit() {
	Keyboard lg_kbd;
	lg_kbd.attach();
	lg_kbd.commit();
	lg_kbd.detach();
	
	return 0;
}

int setStartupEffect(string effect) {
	Keyboard lg_kbd;
	Keyboard::PowerOnEffect powerOnEffect;
	if (lg_kbd.parsePowerOnEffect(effect, powerOnEffect) == true) {
		lg_kbd.attach();
		lg_kbd.setPowerOnEffect(powerOnEffect);
		lg_kbd.commit();
		lg_kbd.detach();
		return 0;
	}
	return 1;
}

int setKey(string key, string color, bool commit) {
	Keyboard lg_kbd;
	Keyboard::KeyAddress keyAddress;
	if (lg_kbd.parseKey(key, keyAddress) == true) {
		Keyboard::KeyColors colors;
		if (lg_kbd.parseColor(color, colors) == true) {
			Keyboard::KeyValue keyValue;
			keyValue.key = keyAddress;
			keyValue.colors = colors;
			lg_kbd.attach();
			lg_kbd.setKey(keyValue);
			if (commit == true) lg_kbd.commit();
			lg_kbd.detach();
			return 0;
		}
	}
	return 1;
}

int setAllKeys(string color, bool commit) {
	Keyboard lg_kbd;
	Keyboard::KeyColors colors;
	if (lg_kbd.parseColor(color, colors) == true) {
		lg_kbd.attach();
		lg_kbd.setAllKeys(colors);
		if (commit == true) lg_kbd.commit();
		lg_kbd.detach();
		return 0;
	}
	return 1;
}

int setGroupKeys(string groupKeys, string color, bool commit) {
	Keyboard lg_kbd;
	Keyboard::KeyGroup keyGroup;
	if (lg_kbd.parseKeyGroup(groupKeys, keyGroup) == true) {
		Keyboard::KeyColors colors;
		if (lg_kbd.parseColor(color, colors) == true) {
			lg_kbd.attach();
			lg_kbd.setGroupKeys(keyGroup, colors);
			if (commit == true) lg_kbd.commit();
			lg_kbd.detach();
			return 0;
		}
	}
	return 1;
}

int setFXColor(string color) {
	Keyboard lg_kbd;
	Keyboard::KeyColors colors;
	if (lg_kbd.parseColor(color, colors) == true) {
		lg_kbd.attach();
		lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
		lg_kbd.commit();
		lg_kbd.detach();
		lg_kbd.attach();
		lg_kbd.setFXColor(colors);
		lg_kbd.detach();
		return 0;
	}
	return 1;
}

int setFXBreathing(string color, string speed) {
	Keyboard lg_kbd;
	Keyboard::KeyColors colors;
	uint8_t speedValue;
	if (lg_kbd.parseColor(color, colors) == true) {
		if (lg_kbd.parseSpeed(speed, speedValue) == true) {
			lg_kbd.attach();
			lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
			lg_kbd.commit();
			lg_kbd.detach();
			lg_kbd.attach();
			lg_kbd.setFXBreathing(colors, speedValue);
			lg_kbd.detach();
			return 0;
		}
	}
	return 1;
}

int setFXColorCycle(string speed) {
	Keyboard lg_kbd;
	Keyboard::KeyColors colors;
	uint8_t speedValue;
	if (lg_kbd.parseSpeed(speed, speedValue) == true) {
		colors.red = 0xff;
		colors.green = 0xff;
		colors.blue = 0xff;
		lg_kbd.attach();
		lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
		lg_kbd.commit();
		lg_kbd.detach();
		lg_kbd.attach();
		lg_kbd.setFXColorCycle(speedValue);
		lg_kbd.detach();
		return 0;
	}
	return 1;
}

int setFXHWave(string speed) {
	Keyboard lg_kbd;
	Keyboard::KeyColors colors;
	uint8_t speedValue;
	if (lg_kbd.parseSpeed(speed, speedValue) == true) {
		colors.red = 0xff;
		colors.green = 0xff;
		colors.blue = 0xff;
		lg_kbd.attach();
		lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
		lg_kbd.commit();
		lg_kbd.detach();
		lg_kbd.attach();
		lg_kbd.setFXHWave(speedValue);
		lg_kbd.detach();
		return 0;
	}
	return 1;
}

int setFXVWave(string speed) {
	Keyboard lg_kbd;
	Keyboard::KeyColors colors;
	uint8_t speedValue;
	if (lg_kbd.parseSpeed(speed, speedValue) == true) {
		colors.red = 0xff;
		colors.green = 0xff;
		colors.blue = 0xff;
		lg_kbd.attach();
		lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
		lg_kbd.commit();
		lg_kbd.detach();
		lg_kbd.attach();
		lg_kbd.setFXVWave(speedValue);
		lg_kbd.detach();
		return 0;
	}
	return 1;
}

int setFXCWave(string speed) {
	Keyboard lg_kbd;
	Keyboard::KeyColors colors;
	uint8_t speedValue;
	if (lg_kbd.parseSpeed(speed, speedValue) == true) {
		colors.red = 0xff;
		colors.green = 0xff;
		colors.blue = 0xff;
		lg_kbd.attach();
		lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
		lg_kbd.commit();
		lg_kbd.detach();
		lg_kbd.attach();
		lg_kbd.setFXCWave(speedValue);
		lg_kbd.detach();
		return 0;
	}
	return 1;
	return 1;
}

int loadProfile(string profileFile) {
	ifstream file;
	
	file.open(profileFile);
	if (file.is_open()) {
		
		string line;
		int lineCount = 1;
		int ind;
		
		Keyboard lg_kbd;
		Keyboard::KeyGroup keyGroup;
		Keyboard::KeyAddress keyAddress;
		Keyboard::KeyValue keyValue;
		Keyboard::KeyColors colors;
		uint8_t speedValue;
		
		map<string, string> var;
		vector<Keyboard::KeyValue> keys;
		
		lg_kbd.attach();
		
		while (!file.eof()) {
			getline(file, line);
			
			if (line.substr(0, 3) == "var") {
				line = line.substr(4);
				ind = line.find(" ");
				var[line.substr(0, ind)] = line.substr(ind + 1, 6);
			} else if (line.substr(0, 1) == "a") {
				line = line.substr(2);
				if (line.substr(0, 1) == "$") {
					ind = line.find(" ");
					line = var[line.substr(1, ind - 1)];
				} else line = line.substr(0, 6);
				if (lg_kbd.parseColor(line, colors) == true) {
					keys.clear();
					lg_kbd.setAllKeys(colors);
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,1) == "g") {
				line = line.substr(2);
				ind = line.find(" ");
				if (lg_kbd.parseKeyGroup(line.substr(0, ind), keyGroup) == true) {
					line = line.substr(ind + 1);
					if (line.substr(0, 1) == "$") {
						ind = line.find(" ");
						line = var[line.substr(1, ind - 1)];
					};
					if (lg_kbd.parseColor(line.substr(0, 6), colors) == true) {
						lg_kbd.setGroupKeys(keyGroup, colors);
					} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,1) == "k") {
				line = line.substr(2);
				ind = line.find(" ");
				if (lg_kbd.parseKey(line.substr(0, ind), keyAddress) == true) {
					line = line.substr(ind + 1);
					if (line.substr(0, 1) == "$") {
						ind = line.find(" ");
						line = var[line.substr(1, ind - 1)];
					}
					if (lg_kbd.parseColor(line.substr(0, 6), colors) == true) {
						keyValue.key = keyAddress;
						keyValue.colors = colors;
						keys.push_back(keyValue);
					} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,1) == "c") {
				lg_kbd.commit();
				lg_kbd.setKeys(&keys[0], keys.size());
				keys.clear();
				lg_kbd.commit();
			} else if (line.substr(0,8) == "fx-color") {
				line = line.substr(9);
				if (line.substr(0, 1) == "$") {
					ind = line.find(" ");
					line = var[line.substr(1, ind - 1)];
				} else line = line.substr(0, 6);
				if (lg_kbd.parseColor(line, colors) == true) {
					keys.clear();
					lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
					lg_kbd.commit();
					lg_kbd.detach();
					lg_kbd.attach();
					lg_kbd.setFXColor(colors);
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,12) == "fx-breathing") {
				line = line.substr(13);
				if (line.substr(0, 1) == "$") {
					ind = line.find(" ");
					line = var[line.substr(1, ind - 1)] + " " + line.substr(ind + 1);
				}
				if (lg_kbd.parseColor(line.substr(0, 6), colors) == true) {
					ind = line.find(" ");
					line = line.substr(ind + 1, 2);
					if (lg_kbd.parseSpeed(line, speedValue) == true) {
						keys.clear();
						lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
						lg_kbd.commit();
						lg_kbd.detach();
						lg_kbd.attach();
						lg_kbd.setFXBreathing(colors, speedValue);
					} else cout<<"Error1 on line "<<lineCount<<" : "<<line<<"\n";
				} else cout<<"Error2 on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,8) == "fx-cycle") {
				line = line.substr(9);
				if (line.substr(0, 1) == "$") {
					ind = line.find(" ");
					line = var[line.substr(1, ind - 1)];
				} else line = line.substr(0, 2);
				if (lg_kbd.parseSpeed(line, speedValue) == true) {
					keys.clear();
					colors.red = 0xff;
					colors.green = 0xff;
					colors.blue = 0xff;
					lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
					lg_kbd.commit();
					lg_kbd.detach();
					lg_kbd.attach();
					lg_kbd.setFXColorCycle(speedValue);
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,8) == "fx-hwave") {
				line = line.substr(9);
				if (line.substr(0, 1) == "$") {
					ind = line.find(" ");
					line = var[line.substr(1, ind - 1)];
				} else line = line.substr(0, 2);
				if (lg_kbd.parseSpeed(line, speedValue) == true) {
					keys.clear();
					colors.red = 0xff;
					colors.green = 0xff;
					colors.blue = 0xff;
					lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
					lg_kbd.commit();
					lg_kbd.detach();
					lg_kbd.attach();
					lg_kbd.setFXHWave(speedValue);
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,8) == "fx-vwave") {
				line = line.substr(9);
				if (line.substr(0, 1) == "$") {
					ind = line.find(" ");
					line = var[line.substr(1, ind - 1)];
				} else line = line.substr(0, 2);
				if (lg_kbd.parseSpeed(line, speedValue) == true) {
					keys.clear();
					colors.red = 0xff;
					colors.green = 0xff;
					colors.blue = 0xff;
					lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
					lg_kbd.commit();
					lg_kbd.detach();
					lg_kbd.attach();
					lg_kbd.setFXVWave(speedValue);
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if (line.substr(0,8) == "fx-cwave") {
				line = line.substr(9);
				if (line.substr(0, 1) == "$") {
					ind = line.find(" ");
					line = var[line.substr(1, ind - 1)];
				} else line = line.substr(0, 2);
				if (lg_kbd.parseSpeed(line, speedValue) == true) {
					keys.clear();
					colors.red = 0xff;
					colors.green = 0xff;
					colors.blue = 0xff;
					lg_kbd.setGroupKeys(Keyboard::KeyGroup::indicators, colors);
					lg_kbd.commit();
					lg_kbd.detach();
					lg_kbd.attach();
					lg_kbd.setFXCWave(speedValue);
				} else cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			} else if ((line.substr(0, 1) != "#") && (line.substr(0, 1) != "")) {
				cout<<"Error on line "<<lineCount<<" : "<<line<<"\n";
			}
		
			lineCount++;
		}
		
		lg_kbd.detach();
		
		file.close();
		
		return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	string str = argv[0];
	size_t split = str.find_last_of("/\\");
	str = str.substr(split + 1);
	if (argc > 1) {
		string argCmd = argv[1];
		if (argCmd == "-h" || argCmd == "--help")             { usage(); return 0; }
		else if (argCmd == "-lk" || argCmd == "--list-keys")  { listkeys(); return 0; }
		else if (argCmd == "-s" && argc == 3)                 return setStartupEffect(argv[2]);
		else if (argCmd == "-a" && argc == 3)                 return setAllKeys(argv[2], true);
		else if (argCmd == "-an" && argc == 3)                return setAllKeys(argv[2], false);
		else if (argCmd == "-g" && argc == 4)                 return setGroupKeys(argv[2], argv[3], true);
		else if (argCmd == "-gn" && argc == 4)                return setGroupKeys(argv[2], argv[3], false);
		else if (argCmd == "-k" && argc == 4)                 return setKey(argv[2], argv[3], true);
		else if (argCmd == "-kn" && argc == 4)                return setKey(argv[2], argv[3], false);
		else if (argCmd == "-c" && argc == 2)                 return commit();
		else if (argCmd == "-p" && argc == 3)                 return loadProfile(argv[2]);
		else if (argCmd == "-fx-color" && argc == 3)          return setFXColor(argv[2]);
		else if (argCmd == "-fx-breathing" && argc == 4)      return setFXBreathing(argv[2], argv[3]);
		else if (argCmd == "-fx-cycle" && argc == 3)          return setFXColorCycle(argv[2]);
		else if (argCmd == "-fx-hwave" && argc == 3)          return setFXHWave(argv[2]);
		else if (argCmd == "-fx-vwave" && argc == 3)          return setFXVWave(argv[2]);
		else if (argCmd == "-fx-cwave" && argc == 3)          return setFXCWave(argv[2]);
	}
	usage();
	return 1;
}
