#include "stdafx.h"

Game_ui* Game_ui::Create(string name)
{
	Game_ui* temp = new Game_ui();
	temp->LoadFile("Game_ui.xml");

	return temp;
}

Game_ui::Game_ui()
{
	p1_letters = new char[6];
	p1_letters[0] = { 'q' };
	p1_letters[1] = { 'w' };
	p1_letters[2] = { 'e' };
	p1_letters[3] = { 'a' };
	p1_letters[4] = { 's' };
	p1_letters[5] = { 'd' };

	p1_random_letters = make_random_p1(p1_letters, 6);

	input_count = 0;

	game_start = false;
}

Game_ui::~Game_ui()
{
}

void Game_ui::Update()
{
	if (INPUT->KeyDown('9'))
	{
		cout << 1 << endl;
		game_start = true;
	}
	if (!game_start) // ������ �Ȳ��ָ� �̻��� �ڽ��� �÷��̾� ���� ����Ǽ� visible �����ϴ�.
	{
		Find("pos1_1")->visible = false;
		Find("pos1_2")->visible = false;
		Find("pos1_3")->visible = false;
		Find("pos1_4")->visible = false;
		Find("pos1_5")->visible = false;
		Find("pos1_6")->visible = false;
		Find("pos1_7")->visible = false;
	}
	if (game_start) // �Է¹������� �ٽ� visible ���־����ϴ�.
	{
		Find("pos1_1")->visible = true;
		Find("pos1_2")->visible = true;
		Find("pos1_3")->visible = true;
		Find("pos1_4")->visible = true;
		Find("pos1_5")->visible = true;
		Find("pos1_6")->visible = true;
		Find("pos1_7")->visible = true;
		set_im_ui();

		char currentInput;
		if (INPUT->KeyDown('Q'))
		{
			currentInput = 'q';
		}
		else if (INPUT->KeyDown('W'))
		{
			currentInput = 'w';
		}
		else if (INPUT->KeyDown('E'))
		{
			currentInput = 'e';
		}
		else if (INPUT->KeyDown('A'))
		{
			currentInput = 'a';
		}
		else if (INPUT->KeyDown('S'))
		{
			currentInput = 's';
		}
		else if (INPUT->KeyDown('D'))
		{
			currentInput = 'd';
		}
		else
		{
			currentInput = '\0';
		}

		// player �Է� Ȯ�� ��ũ�ε�
		if (currentInput != '\0' && currentInput == p1_random_letters[input_count])
		{
			// �� �Է��� ��Ȯ�� ��� ���ϴ� ���� ���� ����
				// 1. ���� ���� Ȯ��
			cout << "����" << endl;
			input_count++;
			set_im_ui();
		}
		else if (currentInput != '\0')
		{
			// �� �Է��� Ʋ�� ���
				// 1. ó������ �ǵ���  (0)
				// 2. ���ġ�� ���ϴ� ��� ������ �ϴ� �Ұ� �Ѽ� ����

			cout << "Ʋ��" << endl;
			input_count = 0;
			set_im_ui();
		}
		if (input_count == p1_random_letters.size())
		{
			// ��� �Է��� ���� ���
				// 1. ������ �缳��
				// 2. �ν��� ��� ������ �ϴ� �� �� �Ѽ� ����
			p1_random_letters = make_random_p1(p1_letters, 6);
			input_count = 0;

		}
		Actor::Update();
	}

	Actor::Update();
}

void Game_ui::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}

vector<char> Game_ui::make_random_p1(char*& _p1_letter, int size)
{
	vector<char> mixed_letters;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, size - 1);

	for (int i = 0; i < 7; i++)
	{
		int index = dis(gen);
		mixed_letters.push_back(_p1_letter[index]);
	}

	return mixed_letters;
}

bool Game_ui::checked_input(const vector<char>& computerLetters, const vector<char>& playerInput, int inputCount)
{
	for (int i = 0; i < inputCount; i++)
	{
		if (playerInput[i] != computerLetters[i])
		{
			return false;
		}
	}

	return true;
}

void Game_ui::set_pos_ui(Actor* _player)
{ // ������ �÷��̾� �Ӹ��� ��ġ�������� ���μ����ϰ� Y�ุ ���� ���� ��Ҿ�� by.����
	this->SetWorldPosX(_player->GetWorldPos().x);
	this->SetWorldPosY(_player->GetWorldPos().y + 3);
	this->SetWorldPosZ(_player->GetWorldPos().z);
}

void Game_ui::set_im_ui()
{
	// Ű�� ���ĺ�, ���� 1. ȸ���̹���, 2. �׸��̹���
	map<char, pair<string, string>> textureMap =
	{
		{'q', {"q_code.png","qn_code.png"}},
		{'w', {"w_code.png","wn_code.png"}},
		{'e', {"e_code.png","en_code.png"}},
		{'a', {"a_code.png","an_code.png"}},
		{'s', {"s_code.png","sn_code.png"}},
		{'d', {"d_code.png","dn_code.png"}}
	};

	// p1_random_letters�� �̹��� ����
		// p1_random_letters ���ڸ� ��ȸ��
			// i < input_count�� �Ǵܱ���
			// �� : ����̹��� ,���� : ȸ���̹���
			// i �� �÷��̾ ��Ȯ�ϰ� �Է��� ���� ������ ������ �� ������
	for (int i = 0; i < p1_random_letters.size(); i++)
	{
		string pos = "pos1_" + to_string(i + 1);
		Find(pos)->texture = RESOURCE->textures.Load
		((i < input_count) ? textureMap[p1_random_letters[i]].second : 
			textureMap[p1_random_letters[i]].first);
	}
}
