program testgeoipex;

uses
  Forms,
  testgeoipex1 in 'testgeoipex1.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
