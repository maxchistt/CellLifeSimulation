import { Component, ViewChild, ElementRef, AfterViewInit, Output, Inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
})
export class HomeComponent implements AfterViewInit {
  @ViewChild('myCanvas', { static: false }) myCanvas: ElementRef;
  socket: WebSocket;
  frame: IDrawEntity[] = [];
  http: HttpClient;
  baseUrl: string;
  size: number[] = [2, 2];
  colors: number[] = [0, 0, 0];
  wrapperWidth: number = 600;
  connections: number = 0;
  collapse: boolean = false;
  scale: boolean = false;

  public canvasContext: CanvasRenderingContext2D;

  ngAfterViewInit(): void {
    this.canvasContext = this.myCanvas.nativeElement.getContext('2d');
  }

  constructor(http: HttpClient, @Inject('BASE_URL') baseUrl: string) {
    this.http = http;
    this.baseUrl = baseUrl;

    this.requestSize();
    this.initWebSocket();
  }

  requestConnections = () => this.http.get<number>(this.baseUrl + `ws/getConnections`).subscribe(this.setConnectionsCounter, error => console.error(error));
  setConnectionsCounter = (num: number) => this.connections = num;

  requestClearCells = () => this.http.get(this.baseUrl + `api/clearCells`).subscribe();
  requestGenerateCells = () => this.http.get(this.baseUrl + `api/generateCells/${30}`).subscribe();

  requestSize = () => this.http.get<number[]>(this.baseUrl + 'api/getSize').subscribe(this.setSize, error => console.error(error));
  setSize = (result: number[]) => this.size = result;

  draw() {
    this.canvasContext.canvas.height = this.size[0];
    this.canvasContext.canvas.width = this.size[1];
    this.frame.forEach((element) => {
      this.canvasContext.strokeStyle = element.color;
      this.canvasContext.fillStyle = element.color;
      this.canvasContext.beginPath();
      this.canvasContext.arc(element.y, element.x, element.size / 2, 0, 2 * Math.PI, true);
      this.canvasContext.fill();
    });
  }

  initWebSocket = () => {
    this.socket = new WebSocket("ws://" + new URL(this.baseUrl).host + "/ws");
    this.socket.onopen = () => { console.log("success"); this.requestConnections(); };
    this.socket.onmessage = (msg) => this.onUpdate(msg);
    this.socket.onclose = () => { console.log("closed"); };
    this.socket.onerror = () => { console.log("error"); };
  }

  onUpdate = (msg: ISocketMessage) => {
    //console.log("income msg", msg.data);
    this.frame = this.parseDrawEntities(msg.data);
    this.calccolors();
    this.draw();
  }

  calccolors = () => {
    this.colors = [0, 0, 0];
    this.frame.forEach(element => {
      if (element.color == "Red") {
        this.colors[0]++;
      } else if (element.color == "Green") {
        this.colors[1]++;
      } else if (element.color == "Blue") {
        this.colors[2]++;
      }
    });
  }

  parseDrawEntities(value: string): IDrawEntity[] {
    let container: IFrameContainer = JSON.parse(value);
    let frame: IDrawEntity[] = container.frame;
    frame.forEach(element => {
      element.color = element.color.substr(7, element.color.length - 8);
    });
    return frame;
  }

}

interface ISocketMessage {
  data: string;
}

interface IFrameContainer {
  frame: IDrawEntity[];
}

interface IDrawEntity {
  x: number;
  y: number;
  size: number;
  color: string;
}