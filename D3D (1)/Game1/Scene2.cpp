#include "stdafx.h"
#include "Solar.h"
#include "Scene2.h"

void Print12()
{
    cout << TIMER->GetWorldTime() << endl;
}


Scene2::Scene2()
{
   




    //RESOURCE->ReleaseAll();
}

Scene2::~Scene2()
{
 
}

void Scene2::Init()
{

    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();


    grid =  Grid::Create();
  
    player = Actor::Create();
    player->LoadFile("Human.xml");
    spear = Actor::Create();
    spear->LoadFile("Spear.xml");
    isFire = false;
    player->Find("SpearSoket")->rotation.x = -PI * 0.25f;
    
    ui = UI::Create();
    ui->LoadFile("UI.xml");

    //ui->mouseOver = Actor::CreateStaticMember;
    //ui->mouseOver = bind(&Actor::RotationZ, player);
    //ui->mouseOver = [=]() {player->rotation.z += DELTA; };
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
    grid->RenderHierarchy();
    player->RenderHierarchy();
    spear->RenderHierarchy();
    Cam->RenderHierarchy();
    ui->RenderHierarchy();
    ImGui::End();

    if (isFire)
    {
        gravity += 3.5f * DELTA;
       
        Vector3 velocity
            = player->Find("SpearSoket")->GetForward() * 20.0f - UP * gravity;
        // 0 ~ -90   -45
        Camera::main = (Camera*)spear->Find("Camera");
        spear->MoveWorldPos(velocity * DELTA);

        spear->Find("Spear")->rotation.x
            = -atan2f(velocity.y, velocity.z);

        cout << spear->Find("Spear")->rotation.x << endl;
    }
    else
    {
        Camera::main = (Camera*)player->Find("BackCam");
        spear->SetWorldPos(player->Find("SpearSoket")->GetWorldPos());
    }
    if (INPUT->KeyDown(VK_SPACE))
    {
        isFire = not isFire;
        gravity = 0.0f;
       
    }
    if (INPUT->KeyPress(VK_UP))
    {
        player->MoveWorldPos(player->GetForward() * 10 * DELTA);
    }


    if (ui->MouseOver())
    {
        //if(INPUT->)
        player->rotation.z += DELTA;
    }



    /*if (INPUT->KeyDown('1'))
    {
        dest = 0;
        t = 0.0f;
    }
    if (INPUT->KeyDown('2'))
    {
        dest = 1;
        t = 0.0f;
    }
    if (INPUT->KeyDown('3'))
    {
        dest = 2;
        t = 0.0f;
    }*/

    

    Cam->Update();
    grid->Update();
    player->Update();
    spear->Update();
    ui->Update();



    /*Cam->GetWorldPos().x;
    Cam->GetWorldPos().z;

    Cam->scale.x;
    Cam->rotation.x;*/


}

void Scene2::LateUpdate()
{
   
}

void Scene2::Render()
{
    Camera::main->Set();



    grid->Render();
    player->Render();
    spear->Render();
    ui->Render();
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

void Scene2::Animation(GameObject* root)
{
   /* GameObject* _src = hand[src]->Find(root->name);
    GameObject* _dest = hand[dest]->Find(root->name);
    root->SetLocalPos(Util::Lerp(_src->GetLocalPos(),
        _dest->GetLocalPos(),t));*/


    //root->rotation =
    //Util::QuaternionToYawPtichRoll(
    //    Util::Lerp(
    //        Quaternion::CreateFromYawPitchRoll(_src->rotation.y, _src->rotation.x, _src->rotation.z),
    //        Quaternion::CreateFromYawPitchRoll(_dest->rotation.y, _dest->rotation.x, _dest->rotation.z)
    //        , t));

    /*root->rotation = Util::Lerp(Util::NormalizeAngles(_src->rotation), Util::NormalizeAngles(_dest->rotation), t);

    for (auto it = root->children.begin();
        it != root->children.end(); it++)
    {
        Animation(it->second);
    }*/
      
}
