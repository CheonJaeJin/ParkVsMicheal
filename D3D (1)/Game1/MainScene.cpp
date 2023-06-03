#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
    //ī�޶�
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();

    //UI
    ui = UI::Create();
    ui->LoadFile("Background.xml");

    button = UI::Create();
    button->LoadFile("Button.xml");

    logo = UI::Create();
    logo->LoadFile("Logo.xml");
}

void MainScene::Release()
{
    Cam->Release();

}

void MainScene::Update()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    Camera::ControlMainCam();
    Cam->SetWorldPos(Vector3(0,0,0));
    Cam->rotation.x = 0;
    Cam->rotation.y = 0;
    Cam->rotation.z = 0;

    //debug
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

    
    ImGui::Begin("Hierarchy"); //Hierarchy ����
    Cam->RenderHierarchy();
    ui->RenderHierarchy();
    logo->RenderHierarchy();
    button->RenderHierarchy();
    ImGui::End(); //Hierarchy ��

    //��ư �浹 ó��
    if (button->MouseOver())
    {
        button->scale.x = 0.55;
        button->scale.y = 0.33;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            SCENE->ChangeScene("SC2")->Init();
            cout << "Button Ui Mouse Over" << endl;
        }
    }
    else if (!button->MouseOver())
    {
        button->scale.x = 0.5;
        button->scale.y = 0.3;
    }

    //������Ʈ
    Cam->Update();
    ui->Update();
    button->Update();
    logo->Update();
}

void MainScene::LateUpdate()
{
    
}

void MainScene::Render()
{
    // ī�޶� ����
    Camera::main->Set();

    //����
    ui->Render();
    button->Render();
    logo->Render();
}

void MainScene::PreRender()
{
}

void MainScene::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}
