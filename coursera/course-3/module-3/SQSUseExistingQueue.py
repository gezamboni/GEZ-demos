import boto3

# Get the device resource
sqs = boto3.resource('sqs')

# Chama um a queue existente
queue = sqs.get_queue_by_name(QueueName='teste')

# Podemos agora acessar os identifiers e atributos
print(queue.url)
print(queue.attributes.get('DelaySeconds'))
