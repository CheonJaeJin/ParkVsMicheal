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
    //신관희
    player = Player::Create();
    player->mainState = MainState::IDLE;
    player2 = Player2::Create();
    player2->SetLocalPosX(15);
    player2->mainState = MainState::IDLE;


    dead = Actor::Create();
    dead->LoadFile("Swim.xml");
    isplayer = true; // 플레이어 true 이면 플레이어 렌더, false면 모델용 dead 렌더

    //천재진
    game_ui = Game_ui::Create();
    game_ui2 = Game_ui::Create();

    //카메라
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
    grid =  Grid::Create();

    /*수업
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
    //Cam->SaveFile("Cam.xml");

    Cam->Release();
}


void Scene2::Update()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::ControlMainCam();

    //debug
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

    //Hierarchy
    ImGui::Begin("Hierarchy");

    //천재진
    game_ui->RenderHierarchy();
    game_ui2->RenderHierarchy(); // 실험용 2생성

    //신관희
    if (!isplayer)// 모델링용 객체입니다 신경ㄴㄴ
        dead->RenderHierarchy();
    else
        player->RenderHierarchy();
        player2->RenderHierarchy();// 실험용 2 생성

    Cam->RenderHierarchy();
    grid->RenderHierarchy();
    /*수업
    player2->RenderHierarchy();
    plane->RenderHierarchy();
    ui->RenderHierarchy();
    */
    ImGui::End();



    /*수업
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

    //천재진
    game_ui->Update();
    game_ui2->Update();

    //신관희
    if (!isplayer) // 모델링용 객체입니다 신경ㄴㄴ
        dead->Update();
    else
        player->Update();
        player2->Update();

}

void Scene2::LateUpdate()
{
    //천재진
    game_ui->set_pos_ui(player);
    game_ui2->set_pos_ui(player2);

}

void Scene2::Render()
{
    Camera::main->Set();
    grid->Render();

    /*수업
    player2->Render();
    plane->Render();
    BLEND->Set(true);
    ui->Render();
    */

    //신관희
    if (!isplayer)// 모델링용 객체입니다 신경ㄴㄴ
        dead->Render();
    else
        player->Render();
        player2->Render();

    //천재진
    game_ui->Render();
    game_ui2->Render();

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
