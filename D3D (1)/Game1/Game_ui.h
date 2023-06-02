#pragma once
class Game_ui : public Actor
{
public:
	static Game_ui* Create(string name = "Game_ui");

	char*			p1_letters;
	vector<char>	p1_random_letters;
	vector<char>	inputed_p1;
	int				input_count;

public:
	bool			game_start;

private:
	Game_ui();
	virtual ~Game_ui();

public:

	void	Update() override;
	void	Release() override;
	vector<char>	 make_random_p1
	(char*& _p1_letter, int size);

	bool			 checked_input
	(const vector<char>& computerLetters, const vector<char>& playerInput, int inputCount);


	void			set_pos_ui(Actor* _player);
	void			set_im_ui();
};

