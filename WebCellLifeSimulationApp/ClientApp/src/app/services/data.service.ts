import { Inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { IDrawEntity, IFrameContainer } from '../interfaces/draw-interfaces';
import { ISocketMessage } from '../interfaces/socket-interfaces';

@Injectable({
  providedIn: 'root'
})

export class DataService {
  socket: WebSocket;
  url: string;
  private clb: (frame: IDrawEntity[]) => void = (frame) => { };

  constructor(private http: HttpClient, @Inject('BASE_URL') baseUrl: string) { this.url = baseUrl || "./"; }

  setUpdateCallback(clb: (frame: IDrawEntity[]) => void): void {
    this.clb = clb;
  }

  reqClearCells(): Promise<void> {
    return this.http.get<void>(this.url + `api/clearCells`).toPromise();
  }

  reqGenerateCells(amount?: number | undefined): Promise<void> {
    return this.http.get<void>(this.url + `api/generateCells/${amount || 30}`).toPromise();
  }

  getSize(): Promise<number[]> {
    return this.http.get<number[]>(this.url + 'api/getSize').toPromise();
  }

  initWebSocket(): Promise<number> {
    return new Promise<number>((res) => {
      this.socket = new WebSocket("ws://" + new URL(this.url).host + "/ws");
      this.socket.onopen = () => { console.log("success"); this.getSocketConnections().then(res, res); };
      this.socket.onmessage = (msg) => { this.onSocketUpdate(msg); }
      this.socket.onclose = () => { console.log("closed"); };
      this.socket.onerror = () => { console.log("error"); };
    });
  }

  private onSocketUpdate = (msg: ISocketMessage): void => { this.clb(parseDrawEntities(msg.data)); }
  private getSocketConnections(): Promise<number> {
    return this.http.get<number>(this.url + `ws/getConnections`).toPromise();
  }
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