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
    ismenu = false;


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

<<<<<<< HEAD
=======
    pool2 = SwimmingPool2::Create();
    pool2->SetWorldPos(Vector3(-8.5, -4, 215));

    //ī�޶�
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
>>>>>>> 3356f08f673593f541c47dd6b5958518d6ca2941
    grid =  Grid::Create();

    /*����
    player2 = Actor::Create();
    player2->LoadFile("Human.xml");
    player2->Find("SpearSoket")->rotation.x = -PI * 0.25f;
    plane = Actor::Create();
    plane->LoadFile("Plane.xml");
    t = 1.0f;
    tR = 1.0f;
    ui = UI::Create();
    ui->LoadFile("UI.xml");
    */
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
    Cam->SetWorldPosY(player->GetWorldPos().y + 10);
    Cam->SetWorldPosZ(player->GetWorldPos().z - 10);
    Cam->rotation.x = 35 * TORADIAN;
    Cam->rotation.y = 0;
    Cam->rotation.z = 0;

    Cam2->SetWorldPosX(player2->GetWorldPos().x);
    Cam2->SetWorldPosY(player2->GetWorldPos().y + 10);
    Cam2->SetWorldPosZ(player2->GetWorldPos().z - 10);
    Cam2->rotation.x = 35 * TORADIAN;
    Cam2->rotation.y = 0;
    Cam2->rotation.z = 0;
    Camera::ControlMainCam();

    //debug
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

    //Hierarchy
    ImGui::Begin("Hierarchy");

    //���ȣ
    pool->RenderHierarchy();
    pool2->RenderHierarchy();

    //õ����
    game_ui->RenderHierarchy();

    //�Ű���
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->RenderHierarchy();
    else
        player->RenderHierarchy();
        player2->RenderHierarchy();// ����� 2 ����

    exitbutton->RenderHierarchy();
    pausebutton->RenderHierarchy();
    playbutton->RenderHierarchy();
    Cam2->RenderHierarchy();
    Cam->RenderHierarchy();
    grid->RenderHierarchy();
    
    /*����
    player2->RenderHierarchy();
    plane->RenderHierarchy();
    ui->RenderHierarchy();
    */
    ImGui::End();



    /*����
    if (INPUT->KeyDown(VK_RBUTTON))
    {
        Ray CamToMouseRay;
        CamToMouseRay = Util::MouseToRay(INPUT->position, Camera::main);
        Vector3 hit;
        if (plane->Intersect(CamToMouseRay, hit))
        {
            src = dead->GetWorldPos();
            dest = hit;
            t = 0.0f;
            Vector3 disV = dest - src;
            dis = disV.Length();

            srcR =dead->rotation.y + PI * 0.5f;
            destR = -atan2f(disV.z, disV.x);

            disR = 0.0f;
            tR = 0.0f;
        }
    }
    if (t < 1.0f)
    {
        t += DELTA * 10.0f / dis ;
        dead->SetWorldPosX(Util::Lerp(src, dest, t).x);
        dead->SetWorldPosZ(Util::Lerp(src, dest, t).z);
    }
    if (tR < 1.0f)
    {
        dead->rotation.y = Util::LerpRotation(srcR, destR, tR, disR) - PI *0.5f;
        tR += DELTA * 3.14f / disR;
    }
    player2->Update();
    plane->Update();
    ui->Update();
    */

    grid->Update();
    Cam->Update();
    Cam2->Update();

    //���ȣ
    pool->Update();
    pool2->Update();

    //õ����
    game_ui->Update();

    //�Ű���
    if (pausebutton->MouseOver())
    {
        pausebutton->scale.x = 0.25;
        pausebutton->scale.y = 0.25;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            ismenu = true;
        }
    }
    else if (!pausebutton->MouseOver())
    {
        pausebutton->scale.x = 0.2;
        pausebutton->scale.y = 0.2;
    }
    if (ismenu)
    {
        TIMER->deltaScaleTime = 0;
    }
    if (exitbutton->MouseOver())
    {
        exitbutton->scale.x = 0.55;
        exitbutton->scale.y = 0.35;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            SCENE->ChangeScene("MC")->Init();
        }
    }
    else if (!exitbutton->MouseOver())
    {
        exitbutton->scale.x = 0.5;
        exitbutton->scale.y = 0.3;
    }
    if (playbutton->MouseOver())
    {
        playbutton->scale.x = 0.55;
        playbutton->scale.y = 0.35;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            ismenu = false;
            // Ÿ�̸�Ŭ���� ��� ���� �ΰ� Public���� �̵�!
            TIMER->deltaScaleTime = TIMER->deltaTime * App.deltaScale;
        }
    }
    else if (!playbutton->MouseOver())
    {
        playbutton->scale.x = 0.5;
        playbutton->scale.y = 0.3;
    }
    exitbutton->Update();
    pausebutton->Update();
    playbutton->Update();

    if (!isplayer) // �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Update();
    else
        player->Update();
        player2->Update();

}

void Scene2::LateUpdate()
{
    //õ����
    game_ui->set_pos_ui(player, player2);

}

void Scene2::Render()
{
    Camera::main->Set();
    //grid->Render();

    /*����
    player2->Render();
    plane->Render();
    BLEND->Set(true);
    ui->Render();
    */
    //���ȣ
    pool->Render();
    pool2->Render();
    //�Ű���
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Render();
    else
    {
        player->Render();
        player2->Render();
    }
    //pausebutton->Render();
    //if (ismenu)
    //{
    //    exitbutton->Render();
    //    playbutton->Render();
    //}

    //õ����
    game_ui->Render();

    Cam2->Set();// ķ2���Ѵ��� ��δ� �����ѹ����ؾ���!
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
    }
    game_ui->Render();
}

void Scene2::PreRender()
{
}

void Scene2::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}
