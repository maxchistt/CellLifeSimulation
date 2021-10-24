import { Component, ViewChild, ElementRef, AfterViewInit, Output, Inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { IDrawEntity, IFrameContainer } from '../interfaces/draw-interfaces';
import { ISocketMessage } from '../interfaces/socket-interfaces';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent {
  socket: WebSocket;

  frame: IDrawEntity[] = [];
  size: number[] = [2, 2];

  http: HttpClient;
  baseUrl: string;

  wrapperWidth: number = 600;
  connections: number = 0;
  collapse: boolean = false;

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

  initWebSocket = () => {
    this.socket = new WebSocket("ws://" + new URL(this.baseUrl).host + "/ws");
    this.socket.onopen = () => { console.log("success"); this.requestConnections(); };
    this.socket.onmessage = (msg) => { this.onUpdate(msg); }
    this.socket.onclose = () => { console.log("closed"); };
    this.socket.onerror = () => { console.log("error"); };
  }

  onUpdate = (msg: ISocketMessage): void => { this.frame = parseDrawEntities(msg.data); }

}

function parseDrawEntities(value: string): IDrawEntity[] {
  try {
    let container: IFrameContainer = JSON.parse(value);
    let frame: IDrawEntity[] = container.frame;
    frame.forEach(element => {
      element.color = element.color.substr(7, element.color.length - 8);
    });
    return frame;
  } catch (e) {
    console.error("ошибка парсинга frame", e);
  }
}