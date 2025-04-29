<?php
namespace App\Controllers;

use App\Config\Pusher as PusherConfig;
use CodeIgniter\RESTful\ResourceController;
use Pusher\Pusher;

class LogController extends ResourceController
{
    protected $modelName = 'App\Models\LogModel';
    protected $format    = 'json';

    public function index()
    {
        return $this->respond($this->model->findAll());
    }

    public function create()
    {
        $sensor_id = $this->request->getPost('sensor_id');
        $mensagem  = $this->request->getPost('mensagem');
        $file      = $this->request->getFile('imagem');

        if (! $sensor_id) {
            return $this->fail("ID do sensor é obrigatório.");
        }

        $imageUrl = null;
        if ($file && $file->isValid()) {
            $newName = $file->getRandomName();
            $file->move('public/uploads/', $newName);
            $imageUrl = base_url("public/uploads/" . $newName);
        }

        // Criando o log no banco de dados
        $logId = $this->model->insert([
            'sensor_id' => $sensor_id,
            'imagem'    => $imageUrl,
            'mensagem'  => $mensagem,
        ]);

        $logData = [
            'id'        => $logId,
            'sensor_id' => $sensor_id,
            'imagem'    => $imageUrl,
            'mensagem'  => $mensagem,
            'timestamp' => date('Y-m-d H:i:s'),
        ];

        // Configurando e enviando o evento pelo Pusher
        $pusherConfig = PusherConfig::getConfig();
        $pusher       = new Pusher(
            $pusherConfig['key'],
            $pusherConfig['secret'],
            $pusherConfig['app_id'],
            [
                'cluster' => $pusherConfig['cluster'],
                'useTLS'  => $pusherConfig['useTLS'],
            ]
        );

        $pusher->trigger('movimentacao', 'novo_log', $logData);

        return $this->respondCreated(["message" => "Log registrado e notificado com sucesso!", "data" => $logData]);
    }
}
