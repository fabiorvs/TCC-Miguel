<?php

namespace App\Models;

use CodeIgniter\Model;

class SensorModel extends Model
{
    protected $table      = 'sensores';
    protected $primaryKey = 'id';

    protected $allowedFields = ['nome', 'descricao', 'localizacao', 'status', 'created_at', 'updated_at', 'deleted_at'];

    protected $useTimestamps = true;
}
