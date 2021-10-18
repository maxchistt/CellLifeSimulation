import { Component, Inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { send } from 'process';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
})
export class HomeComponent {
  socket: WebSocket;
  frame: IDrawEntity[] = [];
  http: HttpClient;
  baseUrl: string;
  size: number[] = [2, 2];
  colors: number[] = [0,0,0];

  connections:number=0;

  constructor(http: HttpClient, @Inject('BASE_URL') baseUrl: string) {
    this.http = http;
    this.baseUrl = baseUrl;

    this.http.get<number[]>(this.baseUrl + 'api/Simulation/getSize').subscribe(this.setSize, error => console.error(error));
    this.initWebSocket(new URL(this.baseUrl).host);

    
  }

  requestConnections = ()=>this.http.get<number>(this.baseUrl + `wsserver/getConnections`).subscribe(this.setConnectionsCounter, error => console.error(error));
  setConnectionsCounter=(num:number)=>this.connections=num;

  clearCells = () => {
    this.http.get(this.baseUrl + `api/Simulation/clearCells`).subscribe();
  }

  generateCells = () => {
    this.http.get(this.baseUrl + `api/Simulation/generateCells/${30}`).subscribe();
  }

  setSize = (result: number[]) => {
    this.size = result;
  }

  initWebSocket = (host: string) => {
    this.socket = new WebSocket("ws://" + host + "/ws");
    this.socket.onopen = () => { console.log("success");this.requestConnections();};
    this.socket.onmessage = (msg) => this.onUpdate(msg);
    this.socket.onclose = () => { console.log("closed"); };
    this.socket.onerror = () => { console.log("error"); };
  }

  onUpdate = (msg: ISocketMessage) => {
    //console.log("income msg", msg.data);
    this.frame = this.parseDrawEntities(msg.data);
    this.calccolors();
  }

  calccolors= ()=>{
    this.colors=[0,0,0];
    this.frame.forEach(element => {
      if(element.color=="Color [Red]"){
        this.colors[0]++;
      }else if(element.color=="Color [Green]"){
        this.colors[1]++;
      }else if(element.color=="Color [Blue]"){
        this.colors[2]++;
      }
    });
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