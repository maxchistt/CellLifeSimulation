import { Component, Inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
})
export class HomeComponent {
  socket: WebSocket;
  frame: IDrawEntity[] = [];
  http: HttpClient;
  baseUrl: string;
  size:number[] = [2,2];

  constructor(http: HttpClient, @Inject('BASE_URL') baseUrl: string) {
    this.http = http;
    this.baseUrl = baseUrl;
    this.http.get<string[]>(this.baseUrl + 'WSSAddress').subscribe(this.initWebSocket, error => console.error(error));
    this.http.get<number[]>(this.baseUrl + 'api/Simulation/getSize').subscribe(this.setSize, error => console.error(error));
    
    this.http.get(this.baseUrl + `api/Simulation/clearCells`);
    this.http.get(this.baseUrl + `api/Simulation/generateCells/${30}`);
  }

  setSize =(result: number[]) =>{
    this.size=result;
  }

  initWebSocket = (result: string[]) => {
    this.socket = new WebSocket(String(result[0]));
    this.socket.onopen = function () { console.log("success"); };
    this.socket.onmessage = (msg) => this.onUpdate(msg);
    this.socket.onclose = function () { console.log("closed"); };
    this.socket.onerror = function () { console.log("error"); };
  }

  onUpdate = (msg: ISocketMessage) => {
    let framearr: IDrawEntity[] = this.parseDrawEntities(msg.data);
    this.frame = framearr;
  }

  parseDrawEntities(value: string): IDrawEntity[] {
    let container: IFrameContainer = JSON.parse(value);
    let frame: IDrawEntity[] = container.frame;
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