<?php

namespace App\Controllers;

use App\Models\SensorModel;
use CodeIgniter\RESTful\ResourceController;

class SensorController extends ResourceController
{
    protected $modelName = 'App\Models\SensorModel';
    protected $format    = 'json';

    public function create()
    {
        $data = [
            'nome'        => $this->request->getPost('nome'),
            'descricao'   => $this->request->getPost('descricao'),
            'localizacao' => $this->request->getPost('localizacao'),
            'status'      => $this->request->getPost('status') ?? 'ativo',
        ];

        if ($this->model->insert($data)) {
            return $this->respondCreated(["message" => "Sensor cadastrado com sucesso!"]);
        }

        return $this->fail("Erro ao cadastrar sensor");
    }
}
