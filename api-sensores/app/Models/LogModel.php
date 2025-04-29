<?php
namespace App\Models;

use CodeIgniter\Model;

class LogModel extends Model
{
    protected $table      = 'logs';
    protected $primaryKey = 'id';

    protected $allowedFields = ['sensor_id', 'imagem', 'mensagem', 'created_at', 'updated_at', 'deleted_at'];

    protected $useTimestamps = true;
}
