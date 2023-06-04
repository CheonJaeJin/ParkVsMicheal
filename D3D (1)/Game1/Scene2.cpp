#include "stdafx.h"
#include "Solar.h"
#include "Scene2.h"

Scene2::Scene2()
{

}

Scene2::~Scene2()
{
 
}

void Scene2::Init()
{
    //�Ű���
    player = Player::Create();
    player->mainState = MainState::IDLE;
    player2 = Player2::Create();
    player2->SetLocalPosX(15);
    player2->mainState = MainState::IDLE;


    dead = Actor::Create();
    dead->LoadFile("Swim.xml");
    isplayer = true; // �÷��̾� true �̸� �÷��̾� ����, false�� �𵨿� dead ����

    exitbutton = UI::Create();
    exitbutton->LoadFile("exitbutton.xml");
    pausebutton = UI::Create();
    pausebutton->LoadFile("pausebutton.xml");
    playbutton = UI::Create();
    playbutton->LoadFile("playbutton.xml");
    cam1pause = UI::Create();
    cam1pause->LoadFile("campause1.xml");
    cam2pause = UI::Create();
    cam2pause->LoadFile("campause2.xml");
    ismenu = false;
    isstop = false;
    isstoptime = 0;

    //ī�޶�
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Cam2 = Camera::Create();
    Cam2->LoadFile("Cam2.xml");

    Camera::main = Cam;
    Cam->width = App.GetHalfWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetHalfWidth();
    Cam->viewport.height = App.GetHeight();

    Cam2->width = App.GetHalfWidth();
    Cam2->height = App.GetHeight();
    Cam2->viewport.width = App.GetHalfWidth();
    Cam2->viewport.height = App.GetHeight();
    Cam2->viewport.x = App.GetHalfWidth();

    //õ����
    game_ui = Game_ui::Create();

    //���ȣ
    pool = SwimmingPool::Create();
    pool->SetWorldPos(Vector3(-8.5,-4,15));

    grid =  Grid::Create();


}

void Scene2::Release()
{
    Cam->Release();
    Cam2->Release();
}


void Scene2::Update()
{
    //Camera::main->width = App.GetWidth();
    //Camera::main->height = App.GetHeight();
    //Camera::main->viewport.width = App.GetWidth();
    //Camera::main->viewport.height = App.GetHeight();

    Cam->SetWorldPosX(player->GetWorldPos().x);
    Cam->SetWorldPosY(player->GetWorldPos().y+10);
    Cam->SetWorldPosZ(player->GetWorldPos().z-10);
    Cam->rotation.x = 35 * TORADIAN;
    Cam->rotation.y = 0;
    Cam->rotation.z = 0;
    //Cam->viewport.width = App.GetHalfWidth();
    //Cam->viewport.height = App.GetHalfHeight();

    Cam2->SetWorldPosX(player2->GetWorldPos().x);
    Cam2->SetWorldPosY(player2->GetWorldPos().y+10);
    Cam2->SetWorldPosZ(player2->GetWorldPos().z-10);
    Cam2->rotation.x = 35 * TORADIAN;
    Cam2->rotation.y = 0;
    Cam2->rotation.z = 0;
    //Cam2->viewport.width = App.GetHalfWidth();
    //Cam2->viewport.height = App.GetHalfHeight();

    Camera::ControlMainCam();

    //debug
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

    //Hierarchy
    ImGui::Begin("Hierarchy");

    //  ���ȣ
    pool->RenderHierarchy();

    // õ����
    game_ui->RenderHierarchy();

    //  �Ű���
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->RenderHierarchy();
    else
    {
        player->RenderHierarchy();
        player2->RenderHierarchy(); // ����� 2 ����
    }
    exitbutton->RenderHierarchy();
    pausebutton->RenderHierarchy();
    playbutton->RenderHierarchy();
    cam1pause->RenderHierarchy();
    cam2pause->RenderHierarchy();
    Cam2->RenderHierarchy();
    Cam->RenderHierarchy();
    grid->RenderHierarchy();

    ImGui::End();



  

    grid->Update();
    Cam->Update();
    Cam2->Update();


    //���ȣ
    pool->Update();

    game_ui->Update();

    //�Ű���
    if (pausebutton->MouseOver())
    {
        pausebutton->scale.x = 0.35;
        pausebutton->scale.y = 0.20;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            ismenu = true;
        }
    }
    else if (!pausebutton->MouseOver())
    {
        pausebutton->scale.x = 0.3;
        pausebutton->scale.y = 0.15;
    }
    if (ismenu)
    {
        isstoptime++;
        if (isstoptime%100 == 50)
        {
            isstop = !isstop;
        }
        TIMER->deltaScaleTime = 0;
    }
    if (exitbutton->MouseOver())
    {
        exitbutton->scale.x = 0.35;
        exitbutton->scale.y = 0.20;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            SCENE->ChangeScene("MC")->Init();
        }
    }
    else if (!exitbutton->MouseOver())
    {
        exitbutton->scale.x = 0.3;
        exitbutton->scale.y = 0.15;
    }
    if (playbutton->MouseOver())
    {
        playbutton->scale.x = 0.35;
        playbutton->scale.y = 0.20;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            isstoptime = 0;
            ismenu = false;
            // Ÿ�̸�Ŭ���� ��� ���� �ΰ� Public���� �̵�!
            TIMER->deltaScaleTime = TIMER->deltaTime * App.deltaScale;
        }
    }
    else if (!playbutton->MouseOver())
    {
        playbutton->scale.x = 0.3;
        playbutton->scale.y = 0.15;
    }
    exitbutton->Update();
    pausebutton->Update();
    playbutton->Update();
    cam1pause->Update();
    cam2pause->Update();


    if (!isplayer) // �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Update();
    else
    {
        player->Update();
        player2->Update();
    }

}

void Scene2::LateUpdate()
{
    game_ui->set_pos_ui(player, player2);

}

void Scene2::Render()
{
    Camera::main->Set();
    //grid->Render();
    // 
    pool->Render();
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Render();
    else
    {
        player->Render();
        player2->Render();
    }
    if (ismenu)
    {
        if (isstop)
        {
            cam1pause->Render();
        }
    }
    game_ui->Render();

    Cam2->Set();
    /// <summary>
    /// //////////////////////////////////
    /// </summary>
    pool->Render();
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Render();
    else
    {
        player->Render();
        player2->Render();
    }

    pausebutton->Render();
    if (ismenu)
    {
        exitbutton->Render();
        playbutton->Render();
        if (isstop)
        {
            cam2pause->Render();
        }
    }
    game_ui->Render();

}


void Scene2::PreRender()
{
}

void Scene2::ResizeScreen()
{
    // Cam->width = App.GetWidth();
    // Cam->height = App.GetHeight();
    // Cam->viewport.width = App.GetWidth();
    // Cam->viewport.height = App.GetHeight();
    // 
    // Cam2->width = App.GetWidth();
    // Cam2->height = App.GetHeight();
    // Cam2->viewport.width = App.GetWidth();
    // Cam2->viewport.height = App.GetHeight();
}
